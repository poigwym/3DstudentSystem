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
	D3DMATERIAL9   *pMaterial; // 网格的材质信息  
	LPDIRECT3DTEXTURE9 *pTexture; // 网格的纹理信息  
	DWORD Mtnum;

	LPD3DXBUFFER pAdjBuffer;

	std::vector<D3DXVECTOR3> m_vtx;
	std::vector<DWORD> m_vtxindices;
	std::vector< std::vector<DWORD> > m_adjface;  // 第i个面的邻接面的下标

	Mesh(char *catalog, char *filename);
	// 载入mesh顶点
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