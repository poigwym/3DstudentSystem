#pragma once


#include"d3dutil.h"

extern LPDIRECT3DDEVICE9 gdevice;
extern ID3DXMesh *g_box, *g_ball;


struct colorvertex {
	colorvertex();
	colorvertex(D3DXVECTOR3 pos, D3DCOLOR col) { position = pos; color = col; }
	D3DXVECTOR3 position;
	D3DCOLOR color;
	static const DWORD FVF = (D3DFVF_XYZ | D3DFVF_DIFFUSE);
};

inline void drawline(D3DXVECTOR3 a, D3DXVECTOR3 b) 
{
	colorvertex vert[] = { colorvertex( a, 0xffff0000),colorvertex(b, 0xff00ff00)};
	gdevice->SetFVF(colorvertex::FVF);
	gdevice->DrawPrimitiveUP(D3DPT_LINESTRIP, 1, &vert[0], sizeof(colorvertex));
}


struct VTX2D {
	float x, y, z, rhw;
	float color;
	VTX2D() {} 
	VTX2D(float x, float y, float c) : x(x), y(y), z(0), rhw(1), color(c) {} 
	static const DWORD FVF = (D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
};

inline void drawline2D(POINT a, POINT b)
{
	VTX2D vert[] = { VTX2D(a.x, a.y, D3DCOLOR_XRGB(0, 0, 0)), VTX2D(b.x, b.y, D3DCOLOR_XRGB(0, 0, 0)) };
	gdevice->SetFVF(VTX2D::FVF);
	gdevice->DrawPrimitiveUP(D3DPT_LINESTRIP, 1, &vert[0], sizeof(VTX2D));
}


struct TextureVertex {
	float x, y, z;
	float u, v;
	TextureVertex() {}
	TextureVertex(float x, float y, float z, float u, float v) :x(x), y(y), z(z), u(u), v(v) {}
	static const DWORD FVF = (D3DFVF_XYZ | D3DFVF_TEX1);
};

inline void drawTexture(LPDIRECT3DTEXTURE9 tex)
{
		TextureVertex vtx[] = {
		TextureVertex(-1.0f, -1.0f, 0.0f, 0.0f, 1.0f),
		TextureVertex(-1.0f, 1.0f,  0.0f, 0.0f, 0.0f),
		TextureVertex(1.0f,  -1.0f, 0.0f, 1.0f, 1.0f),
		TextureVertex(1.0f,  1.0f,  0.0f, 1.0f, 0.0f),
	};

	// alpha blend
	// op = add
	gdevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	gdevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	gdevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	gdevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	gdevice->SetFVF(TextureVertex::FVF);
	gdevice->SetTexture(0, tex);
	gdevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vtx, sizeof(TextureVertex));
	gdevice->SetRenderState(D3DRS_ALPHABLENDENABLE, 0);
}

inline void drawball(D3DXVECTOR3 pos, float r) 
{
	static D3DXMATRIX world, scale;
	D3DXMatrixTranslation(&world, pos.x, pos.y, pos.z);
	D3DXMatrixScaling(&scale, r,r,r);
	world = scale*world;
	gdevice->SetTransform(D3DTS_WORLD, &world);
	g_ball->DrawSubset(0);
}

inline void drawbox(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	static D3DXMATRIX world, scale;
	D3DXMatrixTranslation(&world, pos.x, pos.y, pos.z);
	D3DXMatrixScaling(&scale, size.x, size.y, size.z);
	world = scale*world;
	gdevice->SetTransform(D3DTS_WORLD, &world);
	g_ball->DrawSubset(0);
}

