//
//
//
//#include"d3dutil.h"
//#include"silhouette.h"
//
//#include<iostream>
//using namespace std;
//using namespace d3d;
//
//#define FUCK  MessageBox(0, L"fuck",0,0)
//
//LPDIRECT3DDEVICE9 d3dDevice;
//
//IDirect3DVertexShader9 *toonvs, *outlinevs;
//ID3DXConstantTable *toonTable, *outlineTable;
//D3DXHANDLE  WorldHandle, ViewProjHandle, ViewHandle, lightdirHandle, lightcolorHandle;
//D3DXHANDLE  WorldViewHandle1, ProjHandle1;
//D3DXVECTOR4 lightdir;
//D3DXVECTOR4 lightcolor;
//LPDIRECT3DTEXTURE9 ptexture;
//
//ID3DXMesh *teapot;
//Silhouette *outline;
//
//void init() {
//	HRESULT hr;
//	ID3DXBuffer *shader = 0;
//	ID3DXBuffer *errorbuffer = 0;
//
//	//编译， 创建缓存, 常量表
//	hr = D3DXCompileShaderFromFile("toon.hlsl",
//		0, 0, "VS_Main", "vs_2_0", D3DXSHADER_DEBUG,
//		&shader, &errorbuffer, &toonTable);
//
//	if (FAILED(hr)) {
//		MessageBox(0, "compile toon fail", 0, 0);
//		return;
//	}
//
//	// 创建 vertex shader
//	hr = d3dDevice->CreateVertexShader((DWORD*)shader->GetBufferPointer(), &toonvs);
//	if (FAILED(hr)) {
//		MessageBox(0, "create toonvs fail", 0, 0);
//		return;
//	}
//
//	RELEASE(shader);
//
//
//	// 获取句柄
//	WorldHandle = toonTable->GetConstantByName(0, "WorldMat");
//	ViewProjHandle = toonTable->GetConstantByName(0, "ViewProjMat");
//	ViewHandle = toonTable->GetConstantByName(0, "ViewMat");
//	lightdirHandle = toonTable->GetConstantByName(0, "lightdir");
//	lightcolorHandle = toonTable->GetConstantByName(0, "lightcolor");
//
//
//	toonTable->SetDefaults(d3dDevice);
//	lightdir = D3DXVECTOR4(-0.57f, 0.57f, -0.55f, 0.0f);
//	lightcolor = D3DXVECTOR4(0,0,1,1.0f);
//
//	toonTable->SetVector(d3dDevice, lightdirHandle, &lightdir);
//	toonTable->SetVector(d3dDevice, lightcolorHandle, &lightcolor);
//
//
//	/// outline HLSL
//	hr = D3DXCompileShaderFromFile("outline.hlsl",
//		0, 0, "VS_Main", "vs_2_0", D3DXSHADER_DEBUG,
//		&shader, &errorbuffer, &outlineTable);
//
//	if (FAILED(hr)) {
//		MessageBox(0, "compile outline fail", 0, 0);
//		return;
//	}
//
//
//	hr = d3dDevice->CreateVertexShader((DWORD*)shader->GetBufferPointer(), &outlinevs);
//	if (FAILED(hr)) {
//		MessageBox(0, "create outlinevs fail", 0, 0);
//		return;
//	}
//  
//	RELEASE(shader);
//	WorldViewHandle1 = outlineTable->GetConstantByName(0, "WorldViewMat");
//	ProjHandle1 = outlineTable->GetConstantByName(0, "ProjMat");
//
//	outlineTable->SetDefaults(d3dDevice);
//
//	//texture
//	D3DXCreateTextureFromFile(d3dDevice, "toonshade.bmp", &ptexture);	//创建
//
//	// teapot
//	ID3DXBuffer *adjbuffer;
//	D3DXCreateTeapot(d3dDevice, &teapot, &adjbuffer);
//
//	// outline 
//	outline = new Silhouette(d3dDevice, teapot, adjbuffer);
//
//
//	D3DVIEWPORT9 vp = { 0, 0, WID, HEI, 0, 1 };  //(0,0)在窗口的起点 (WID,HEI), 最小最大z缓冲
//	d3dDevice->SetViewport(&vp);
//}
//
//void render() {
//	
//	// world
//	D3DXMATRIX worldmat, roty, rotx;
//	static float dy = 0, dx = 0;
//	dy += 0.001f;
//	D3DXMatrixRotationY(&roty, dy);
//	D3DXMatrixRotationX(&rotx, dx);
//	D3DXMatrixIdentity(&worldmat);
//	worldmat = rotx* roty*worldmat;
//	//d3dDevice->SetTransform(D3DTS_WORLD, &worldmat);
//
//	static float dd = 0;
//	dd += 0.01;
//	//camara
//	D3DXVECTOR3 vEyePt(0, 0, -10 );
//	D3DXVECTOR3 vLookatPt(0, 0, 0);
//	D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);
//	D3DXMATRIX matView;
//	D3DXMatrixLookAtLH(&matView, &vEyePt, &vLookatPt, &vUpVec);
//	d3dDevice->SetTransform(D3DTS_VIEW, &matView);
//
//	//projection
//	D3DXMATRIX matProj;
//	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4, 1.0f, 1.0f, 1000.0f);
//	d3dDevice->SetTransform(D3DTS_PROJECTION, &matProj);
//
//	D3DXMATRIX  viewprojmat;
//	D3DXMatrixMultiply(&viewprojmat, &matView, &matProj);
//
//
//	d3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
//	// output
//	d3dDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xffffffff, 1.0f, 0);
//	d3dDevice->BeginScene();
//	d3dDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
//
//	// 矩阵放到顶点着色器
//	// 开vertex shader
//	toonTable->SetMatrix(d3dDevice, WorldHandle, &worldmat);
//	d3dDevice->SetVertexShader(toonvs);
//	toonTable->SetMatrix(d3dDevice, ViewProjHandle, &viewprojmat);
//	toonTable->SetMatrix(d3dDevice, ViewHandle, &matView);
//	d3dDevice->SetTexture(0, ptexture);
//	teapot->DrawSubset(0);
//
//	// set outline vs
//	d3dDevice->SetTexture(0, 0);
//	d3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
//	d3dDevice->SetVertexShader(outlinevs);
//	D3DXMATRIX worldview = worldmat*matView;
//	outlineTable->SetMatrix(d3dDevice, WorldViewHandle1, &worldview);
//	outlineTable->SetMatrix(d3dDevice, ProjHandle1, &matProj);
//	outline->render();
//
//	d3dDevice->EndScene();
//	d3dDevice->Present(0, 0, 0, 0);
//}
//
//void clear() {
//	RELEASE(teapot);
//	RELEASE(toonvs);
//	RELEASE(toonTable);
//	RELEASE(ptexture);
//	delete outline;
//}
//
//
//int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lptCmdLine, int nCmd) 
//{
//	if(!WinInit(hInstance, &d3dDevice))  {
//		return 0;
//	}
//
//	init();
//
//	GameLoop(render);
//
//	clear();
//	return 0;
//}