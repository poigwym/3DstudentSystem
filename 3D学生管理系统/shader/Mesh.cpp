
#include"Mesh.h"

Mesh::Mesh(char *catalog, char *filename)
{
	char filepath[222];
	LPD3DXBUFFER pMtrlBuffer = NULL;
	pAdjBuffer = 0;
	strcpy(filepath, catalog);
	strcat(filepath, filename);
	if (FAILED(D3DXLoadMeshFromX(filepath, D3DXMESH_MANAGED, gdevice,
		&pAdjBuffer, &pMtrlBuffer, NULL, &Mtnum, &m_pmesh))) {
		MessageBox(0, "load mesh fail ", 0, 0);
		return;
	}

	//二，读取材质和纹理数据  
	D3DXMATERIAL*pMtrls = (D3DXMATERIAL*)pMtrlBuffer->GetBufferPointer(); //创建一个D3DXMATERIAL结构体用于读取材质和纹理信息  
	pMaterial = new D3DMATERIAL9[Mtnum];
	pTexture = new LPDIRECT3DTEXTURE9[Mtnum];

	for (DWORD i = 0; i<Mtnum; i++) {
		//获取材质，并设置环境光的颜色值  
		pMaterial[i] = pMtrls[i].MatD3D;
		pMaterial[i].Ambient = pMaterial[i].Diffuse;
		strcpy(filepath, catalog);
		strcat(filepath, pMtrls[i].pTextureFilename);
		if(FAILED(D3DXCreateTextureFromFileA(gdevice, filepath, &pTexture[i]))) 
			MessageBox(0, "load mesh texture fail ", 0, 0);
	}

	LoadData();			// load vertex and face 

	RELEASE(pMtrlBuffer);
}

// 载入mesh顶点
void Mesh::LoadData()
{

	// adjface
	m_adjface.resize((int)m_pmesh->GetNumFaces());
	DWORD *adj = (DWORD*)pAdjBuffer->GetBufferPointer();
	for (int i = 0;i<m_pmesh->GetNumFaces();++i)
	{
		for (int j = 0;j<3;++j)
			if (3 * i + j < m_pmesh->GetNumFaces())
				m_adjface[i].push_back(adj[3 * i + j]);
			else
				m_adjface[i].push_back(-1);
	}



	// vertex and indices;
	MeshVertex *vtx = 0;
	m_pmesh->LockVertexBuffer(0, (void**)&vtx);

	WORD *vtxindex = 0;
	m_pmesh->LockIndexBuffer(0, (void**)&vtxindex);

	int cface = m_pmesh->GetNumFaces();
	for (int i = 0;i<cface;++i)
	{
		m_vtx.push_back(vtx[vtxindex[i * 3]].position);
		m_vtx.push_back(vtx[vtxindex[i * 3 + 1]].position);
		m_vtx.push_back(vtx[vtxindex[i * 3 + 2]].position);
	}
	m_pmesh->UnlockVertexBuffer();
	m_pmesh->UnlockIndexBuffer();
}

void Mesh::render() {
	for (DWORD i = 0;i<Mtnum;++i) {
		if (&pMaterial[i]) gdevice->SetMaterial(&pMaterial[i]);
		else gdevice->SetMaterial(&d3d::BLUE_MTRL);
		if (pTexture[i]) gdevice->SetTexture(0, pTexture[i]);
		else gdevice->SetTexture(0, 0);
		m_pmesh->DrawSubset(i);
	}
}