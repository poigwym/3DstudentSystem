#pragma once

#include"d3dutil.h"


extern IDirect3DDevice9 *gdevice;


struct MeshVertex
{
	D3DXVECTOR3 position;
	D3DXVECTOR3 normal;
	D3DXVECTOR2 texcoord;
};


struct Mesh {
	LPD3DXMESH  m_pmesh;
	D3DMATERIAL9   *pMaterial; // ����Ĳ�����Ϣ  
	LPDIRECT3DTEXTURE9 *pTexture; // �����������Ϣ  
	DWORD Mtnum;

	LPD3DXBUFFER pAdjBuffer;

	std::vector<D3DXVECTOR3> m_vtx;
	std::vector<DWORD> m_vtxindices;
	std::vector< std::vector<DWORD> > m_adjface;  // ��i������ڽ�����±�

	Mesh(char *catalog, char *filename);
	// ����mesh����
	void LoadData();
	void render();
	

	void clear() {
		RELEASE(m_pmesh);
		for (DWORD i = 0;i<Mtnum;++i)
			RELEASE(pTexture[i]);
		DELETE(pMaterial);
		RELEASE(pAdjBuffer);
	}
};



inline D3DXVECTOR3  TerrainTrace(D3DXVECTOR3 pos, Mesh *terrain)
{
	D3DXVECTOR3 org = pos + D3DXVECTOR3(0.0f, 1000.0f, 0.0f);
	D3DXVECTOR3 dir = D3DXVECTOR3(0.0f, -1.0f, 0.0f);

	BOOL Hit;
	DWORD FaceIndex;
	FLOAT U;
	FLOAT V;
	FLOAT Dist;

	//Floor-ray intersection test
	D3DXIntersect(terrain->m_pmesh, &org, &dir, &Hit, &FaceIndex, &U, &V, &Dist, NULL, NULL);

	if (Hit)
		pos.y = org.y - Dist;
	return pos;
}