//
//
//
//#include"fsm.h"
//#include"display.h"
//#include"typer.h"
//#define Deg2Rnd(x) D3DX_PI / 180 * (x)
//
//extern HINSTANCE ghInstance;
//extern LPDIRECT3DDEVICE9 gdevice;
//extern Camera *camera;
//extern InputController *dxinput;
//extern TYPER *typer;
//extern ifstream fin;
//App *gapp = new App;				//  interface
//
//extern TYPER *typer;
//
//
//
//ID3DXMesh *teapot;
//
//enum bodyState { stand=1, walk=2  };
//enum Input { dir, space };
//FSMclass *fsm;
//FSMstate *fsmstate;
//
//#define keydown(x) dxinput->KeyDown(x)
//#define keyup(x)  dxinput->KeyUp(x)
//
//void  App::init() {
//
//	D3DXCreateTeapot(gdevice, &teapot, 0);
//	fsm = new FSMclass;
//	fsmstate = new FSMstate(stand);
//	fsmstate->AddTransform(dir, walk);
//	fsm->AddState(fsmstate);
//	fsmstate = new FSMstate(walk);
//	fsmstate->AddTransform(space, stand);
//	fsm->AddState(fsmstate);
//	fsm->m_curstate = stand;
//
//
//}
//
//void App::update() {
//
//	switch(fsm->m_curstate)  {
//		case walk:
//		{
//			if(keydown(DIK_SPACE))
//				fsm->SetTransform(space);
//			break;
//		}
//		case stand:
//		{
//			if(keydown(DIK_SPACE)) 
//				fsm->SetTransform(dir);
//			break;
//		}
//	}
//}
//
//float px, py, pz;
//void App::render() {
//
//	D3DXMATRIX world;
//	switch (fsm->m_curstate) {
//		case walk:
//			pz += 0.01;
//			break;
//		case stand:
//			break;
//	}
//	D3DXMatrixTranslation(&world, px, py, pz);
//	gdevice->SetTransform(D3DTS_WORLD, &world);
//	teapot->DrawSubset(0);
//
//	//if(fsm->m_curstate
//	typer->render(fsm->m_curstate == walk ? "walk" : "stand", 10,10);
//}
//void  App::clear() {
//	RELEASE(teapot);
//	delete fsm;
//}
//
//
////Èë¿Úº¯Êý
//int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lptCmdLine, int nCmd)
//{
//	ghInstance = hInstance;
//	ginit();
//	GameLoop(gdisplay);
//	gclear();
//	return 0;
//}