
#include"silhouette.h"

Silhouette::Silhouette(LPDIRECT3DDEVICE9 _device, ID3DXMesh *mesh, ID3DXBuffer *adjbuffer) 
{
	device = _device;
	vtxbuf = 0;
	indexbuf = 0;
	vtxnum = 0;
	Silhouettenum = 0;
	CreateVtx(mesh, adjbuffer);
	CreateIndex(mesh);
	CreateVertexDeclaration();
}

Silhouette::~Silhouette() {
	RELEASE(vtxbuf);
	RELEASE(indexbuf);
	RELEASE(decl);
}

void Silhouette::CreateVertexDeclaration() {
	D3DVERTEXELEMENT9 _decl[] = {
		{ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
		{ 0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0 },
		{ 0, 24, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 1 },
		{ 0, 36, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 2 },
		D3DDECL_END()
	};

	HRESULT hr = device->CreateVertexDeclaration(_decl, &decl);
	if(FAILED(hr)) {
		MCOUT("CreateVertexDecl fail");
		return;
	}

}





void Silhouette::MakeNormal(ID3DXMesh *mesh, int face, D3DXVECTOR3 *normal) {
	MeshVertex *meshvtx = 0;
	mesh->LockVertexBuffer(0, (void**)&meshvtx);

	WORD *vtxindex = 0;
	mesh->LockIndexBuffer(0, (void**)&vtxindex);

	D3DXVECTOR3 v[3] = {  meshvtx[vtxindex[face*3]].pos, 
												meshvtx[vtxindex[face*3+1]].pos, 
												meshvtx[vtxindex[face*3+2]].pos };

	D3DXVECTOR3 e1 =  v[1] - v[0];
	D3DXVECTOR3 e2 =  v[2] - v[0];
	D3DXVec3Cross(normal, &e1, &e2);
	D3DXVec3Normalize(normal, normal);

	mesh->UnlockVertexBuffer();
	mesh->UnlockIndexBuffer();
}



void Silhouette::CreateVtx(ID3DXMesh *mesh, ID3DXBuffer *adjbuffer) {
	vtxnum = 3*4*mesh->GetNumFaces();
	device->CreateVertexBuffer(
		vtxnum*sizeof(SilhoutteEdgeVtx), D3DUSAGE_WRITEONLY,
		0, D3DPOOL_MANAGED, &vtxbuf, 0);

	SilhoutteEdgeVtx *edgevtx = 0;
	vtxbuf->Lock(0, 0, (void**)&edgevtx, 0);

	MeshVertex *meshvtx = 0;
	mesh->LockVertexBuffer(0, (void**)&meshvtx);

	WORD *vtxindex = 0;
	mesh->LockIndexBuffer(0, (void**)&vtxindex);

	// 每个面三条边
	int i,j;
	DWORD *adj = (DWORD*)adjbuffer->GetBufferPointer();
	for(i = 0; i < mesh->GetNumFaces(); ++i)
	{
		D3DXVECTOR3 facenormal;
		MakeNormal(mesh, i, &facenormal);
		D3DXVECTOR3 adjfacenormal[3];
		// 3个邻接面法线
		// adjfacenormal[0,1,2];
		for(j=0;j<3;++j){
			if(adj[3*i+j] < mesh->GetNumFaces())
				MakeNormal(mesh, adj[3*i+j], adjfacenormal+j);  
			else 
				adjfacenormal[j] = -facenormal;
		}
				
    //A------B
		//|			 |
		//C------D
		// C,D is duplication of A,B
		MeshVertex v[3] = {
			meshvtx[vtxindex[i * 3 ]],
			meshvtx[vtxindex[i * 3 + 1]],
			meshvtx[vtxindex[i * 3 + 2]] };

		for(j=0;j<3;++j) {	
			SilhoutteEdgeVtx A, B, C, D;
			A.pos = v[j].pos;
			A.n = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			A.n1 = facenormal;
			A.n2 = adjfacenormal[j];

			B.pos = v[(j+1)%3].pos;
			B.n = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			B.n1 = facenormal;
			B.n2 = adjfacenormal[j];

			C = A;
			C.n = v[j].n;
			D = B;
			D.n = v[(j+1)%3].n;

			edgevtx[12*i+4*j] = A;
			edgevtx[12*i+4*j+1] = B;
			edgevtx[12*i+4*j+2] = C;
			edgevtx[12*i+4*j+3] = D;
		}

	}
	vtxbuf->Unlock();
	mesh->UnlockVertexBuffer();
	mesh->UnlockIndexBuffer();
}


void Silhouette::CreateIndex(ID3DXMesh *mesh) {

	int edgenum = mesh->GetNumFaces()*3;
	Silhouettenum = edgenum*2;   
	device->CreateIndexBuffer( 6*edgenum*sizeof(WORD), 
		D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &indexbuf, 0);

	WORD *index = 0;
	indexbuf->Lock(0, 0, (void**)&index, 0);
	//0 1
  //2 3
	for(int i=0;i<edgenum;++i) {
		index[i*6] = 4*i;
		index[i*6+1] = 4*i+1;
		index[i*6+2] = 4*i+2;

		index[i*6+3] = 4*i+1;
		index[i*6+4] = 4*i+3;
		index[i*6+5] = 4*i+2;
	}
	indexbuf->Unlock();
}



void Silhouette::render() {
	device->SetVertexDeclaration(decl);
	device->SetStreamSource(0, vtxbuf, 0, sizeof(SilhoutteEdgeVtx));
	device->SetIndices(indexbuf);

	device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, vtxnum, 0, Silhouettenum);
}


