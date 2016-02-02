
#include"navigmesh.h"

#define BUG


NavigationMesh::NavigationMesh(Mesh *meshdata)
{
	m_vis = 0;
	BuildMap(meshdata);
}


void NavigationMesh::BuildMap(Mesh *meshdata)
{
	LPD3DXMESH mesh = meshdata->m_pmesh;
	int cface = mesh->GetNumFaces();
	int i, j;
	m_cells.resize(cface);

	// vertex and indices;
	MeshVertex *vtx = 0;
	mesh->LockVertexBuffer(0, (void**)&vtx);

	WORD *vtxindex = 0;
	mesh->LockIndexBuffer(0, (void**)&vtxindex);

	for(i=0;i<cface;++i) {
		m_cells[i] = new NavigationCell;
		m_cells[i]->init(vtx[vtxindex[3*i]].position, 
										vtx[vtxindex[3*i+1]].position, 
										vtx[vtxindex[3*i+2]].position);
	}

	// adj cells
	DWORD *adj = (DWORD*)meshdata->pAdjBuffer->GetBufferPointer();
	for(i=0;i<cface;++i) 
	{
		for(j=0;j<3;++j) 
			if(adj[3*i+j] < cface)
				m_cells[i]->AddAdjface(m_cells[adj[3*i+j]]);
			else 
				m_cells[i]->AddAdjface(0);
	}
	mesh->UnlockIndexBuffer();
	mesh->UnlockVertexBuffer();
}



NavigationCell* NavigationMesh::Findclosestcell(point2D p)
{
	NavigationCell *res=0;
	float dis;
	for(int i=0;i<m_cells.size();++i) {
		float t  = abs(m_cells[i]->m_midpoint - p);
		if(i==0 || t < dis) {
			dis = t;
			res = m_cells[i];
		}
	}
	return res;
}



bool NavigationMesh::FindPath(D3DXVECTOR3 beg, D3DXVECTOR3 tar) 
{
	// init finding
	point2D beg2D = ToP2D(beg), tar2D = ToP2D(tar);
	int i,j;
	int found=0;
	// init
	for(i=0;i<m_cells.size();++i)  
		m_cells[i]->FindingInit();
	++m_vis;
	begcell = Findclosestcell(tar2D);  // from tar to beg
	tarcell = Findclosestcell(beg2D);


	assert(tarcell != 0);
	assert(begcell != 0);

	// begin search
	priority_queue<NavigationNode> q;
	begcell->vis = m_vis;
	begcell->open = 1;
	begcell->g = 0;
	begcell->h = 0;
	q.push(NavigationNode(begcell));
	while(!q.empty()) 
	{
		NavigationNode curnode = q.top(); 
		NavigationCell *curcell = curnode.cell;
		if(curcell == tarcell) 
		{
			found=1;
			break;
		}
		q.pop();  // throw to close 
		for(i=0;i<curcell->m_adjcell.size();++i) 
		{
			NavigationCell *adjcell = curcell->m_adjcell[i];
			if(!adjcell) continue;
			if(adjcell->vis != m_vis) {
				adjcell->g = curcell->g + curcell->m_edgecost[i];
				adjcell->h = adjcell->ComputeH(beg2D);
				adjcell->open = 1;
				adjcell->vis = m_vis;
				adjcell->precell = curcell;
				for(j=0;j<3;++j) {
					if(adjcell->m_adjcell[j] == curcell) {
						adjcell->m_arrivewall = j;
						break;
					}
				}

				q.push(NavigationNode(adjcell));
			} 
			else if(adjcell->open) {
				float g = curcell->g + curcell->m_edgecost[i];
				if(g < adjcell->g) {
					adjcell->precell = curcell;
					for(j=0;j<3;++j) {
						if(adjcell->m_adjcell[j] == curcell) {
							adjcell->m_arrivewall = j;
							break;
						}
					}
					adjcell->g = g;
					q.push(NavigationNode(adjcell));
				}
			} 
		}
	}
	if(!found) return 0;
	MakePath(tarcell, begcell); // beg -> tar
	return 1;
}


void NavigationMesh::MakePath(NavigationCell *begcell, NavigationCell *tarcell)
{
	m_path.clear();
	for(NavigationCell *t = begcell; t; t=t->precell) 
	{
		m_path.push_back(t->m_midpoint);
		m_path.push_back(t->m_midofwall[t->m_arrivewall]);
	}
}

