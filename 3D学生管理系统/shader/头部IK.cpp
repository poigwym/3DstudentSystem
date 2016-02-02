//
//#include"display.h"
//#include"IKanimation.h"
//
//#define Deg2Rnd(x) D3DX_PI / 180 * (x)
//
//extern HINSTANCE ghInstance;
//extern LPDIRECT3DDEVICE9 gdevice;
//extern Camera *camera;
//extern InputController *dxinput;
//extern TYPER *typer;
//extern ifstream fin;
//
//App *gapp = new App;				//  interface
//
//char *Xname = "soldier.X";
//HeadIK *ik;
//ID3DXEffect *gAnimationEffect;
//ID3DXMesh *teapot;
//
//void  App::init() {
//	ID3DXBuffer *errorbuf = 0;
//	if (FAILED(D3DXCreateEffectFromFile(gdevice, "BlendVertex.fx",
//		0, 0, D3DXSHADER_DEBUG, 0, &gAnimationEffect, &errorbuf))) 
//	{
//		MessageBox(0, (char*)errorbuf->GetBufferPointer(), 0, 0);
//		exit(1);
//		return;
//	}
//	D3DXCreateTeapot(gdevice, &teapot, 0);
//
//	ik = new HeadIK(Xname);
//}
//
//void App::update() {
//
//}
//
//void App::render() {
//
//	D3DXMATRIX world;
//	float px, py, pz;
//	fin >> px >> py >> pz;
//
//
//
//		D3DXMATRIX VP = camera->GetView() * (camera->GetProj());
//		D3DXVECTOR4 lightpos = D3DXVECTOR4(0, 30, -30 , 1 );
//		gAnimationEffect->SetVector("lightpos", &lightpos);
//		gAnimationEffect->SetMatrix("ViewProjMat", &VP);
//		ik->Move(0,0,0);
//		ik->updateHeadIK();
//		ik->Render();
//}
//void  App::clear() {
//	RELEASE(teapot);
//}
//
//
////Èë¿Úº¯Êý
//int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lptCmdLine, int nCmd)
//{
//	ghInstance = hInstance;
//	ginit();
//	GameLoop(grender);
//	gclear();
//	return 0;
//}