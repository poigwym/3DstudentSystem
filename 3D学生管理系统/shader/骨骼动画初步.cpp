//
//
//#include"d3dutil.h"
//#include"animation.h"
//#include"camera.h"
//#include"inputsystem.h"
//using namespace d3d;
//using namespace std;
//
//
//SkinMesh *ani;
//
//
//HWND ghwnd;
//LPDIRECT3DDEVICE9 d3dDevice;
//Camera *camera;
//InputController *dxinput;
//ID3DXMesh *teapot;
//char *Xname = "soldier.X";
//ID3DXEffect *eff;
//
//const int n = 2;
//D3DXMATRIX Pos[n];
//vector<ID3DXAnimationController*> players;
//
//void init() {
//
//	ani = new SkinMesh(Xname, d3dDevice);
//	eff = SkinMesh::effect;
//	
//	vector<string> motionName;
//	ani->extractAnim(motionName);
//	
//
//	for(int i=0;i<n;++i) {
//		D3DXMatrixTranslation(Pos+i,i,0,0);
//		players.push_back(ani->ClonePlayer());
//		ID3DXAnimationSet *anim=0;
//		players[i]->GetAnimationSet(i, &anim);
//		players[i]->SetTrackAnimationSet(0, anim);
//	}
//
//	//viewport
//	D3DVIEWPORT9 vp = { 0, 0, WID, HEI, 0, 1 };
//	d3dDevice->SetViewport(&vp);
//}
//
//void render() {
//	d3dDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xffffffff, 1.0f, 0);
//	d3dDevice->BeginScene();
//
//	//camara
//	D3DXVECTOR3 vEyePt(0, 0, -10);
//	D3DXVECTOR3 vLookatPt(0, 0, 0);
//	D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);
//	D3DXMATRIX matView, matProj, VP;
//	D3DXMatrixLookAtLH(&matView, &vEyePt, &vLookatPt, &vUpVec);
//	d3dDevice->SetTransform(D3DTS_VIEW, &matView);
//
//	//projection
//	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4, 1.0f, (float)WID/HEI, 1000.0f);
//	d3dDevice->SetTransform(D3DTS_PROJECTION, &matProj);
//	
//	D3DXVECTOR4 lightpos = { 0, 30, -30 , 1 };
//	VP = matView * matProj;
//	eff->SetVector("lightpos", &lightpos);
//	eff->SetMatrix("ViewProjMat", &VP);
//  
//	static float tnow = GetTickCount()*0.001, tpre=tnow;
//	tnow = GetTickCount()*0.001;
//
//	//D3DXMATRIX world;
//	//D3DXMatrixIdentity(&world);
//
//	for(int i=0;i<n;++i) {
//		players[i]->AdvanceTime(tnow-tpre, 0);
//		ani->Move(Pos+i);
//		ani->Render();
//	}
//
//	tpre = tnow;
//
//	d3dDevice->EndScene();
//	d3dDevice->Present(0, 0, 0, 0);
//}
//
//void clear() {
//	RELEASE(d3dDevice);
//	DELETE(camera);
//	DELETE(dxinput);
//	DELETE(ani);
//}
////Èë¿Úº¯Êý
//int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lptCmdLine, int nCmd)
//{
//	if (!(ghwnd = WinInit(hInstance, &d3dDevice))) {
//		return 0;
//	}
//	dxinput = new InputController(hInstance, ghwnd, 0);
//
//	init();
//
//	GameLoop(render);
//	clear();
//	return 0;
//}