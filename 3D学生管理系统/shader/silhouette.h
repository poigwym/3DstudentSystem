#pragma once

#include"d3dutil.h"

struct SilhoutteEdgeVtx  {
	D3DXVECTOR3 pos;
	D3DXVECTOR3 n;
	D3DXVECTOR3 n1;   // 邻接面的法线1
	D3DXVECTOR3 n2;
};

// 网格顶点格式
struct MeshVertex {
	D3DXVECTOR3 pos;
	D3DXVECTOR3 n;
	static const DWORD FVF = D3DFVF_XYZ | D3DFVF_NORMAL;
};


struct Silhouette {

	LPDIRECT3DDEVICE9 device;
	IDirect3DVertexBuffer9  *vtxbuf;
	IDirect3DIndexBuffer9  *indexbuf;
	IDirect3DVertexDeclaration9 *decl;

	UINT vtxnum;
	UINT Silhouettenum;  // 轮廓缩面*2

	Silhouette() {}
	Silhouette(LPDIRECT3DDEVICE9 device, ID3DXMesh *mesh, ID3DXBuffer *adjbuffer);
	~Silhouette();

	void CreateVertexDeclaration();
	void MakeNormal(ID3DXMesh *mesh, int i, D3DXVECTOR3 *normal);
	void CreateVtx(ID3DXMesh *mesh, ID3DXBuffer *adjbuffer);
	void CreateIndex(ID3DXMesh *mesh);
	void render();

};