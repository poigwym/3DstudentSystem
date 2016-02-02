//
//
//
//
//#include"d3dutil.h"
//#include"animation.h"
//#include"camera.h"
//#include"inputsystem.h"
//using namespace d3d;
//
//using namespace std;
//#define FUCK  MessageBox(0, "fuck",0,0)
//#define mout(x) MessageBox(0, x, 0, 0)
//
//HWND ghwnd;
//LPDIRECT3DDEVICE9 d3dDevice;
//Camera *camera;
//InputController *dxinput;
//ID3DXMesh *teapot;
//char *Xname = "soldier.X";
//SkinMesh *ani;
//ID3DXEffect *eff;
//
//void init() {
//
//	camera = new Camera(d3dDevice, WID, HEI);
//	camera->SetEye(0, 0, -50);
//	camera->SetTar(0, 0, 0);
//	camera->SetView();
//	camera->SetProj();
//	camera->SetViewport();
//
//	D3DXCreateTeapot(d3dDevice, &teapot, 0);
//	ani = new SkinMesh(Xname, d3dDevice);
//	eff = SkinMesh::effect;
//}
//
//void update() {
//	dxinput->update();
//	if (dxinput->KeyDown(DIK_A)) camera->move(-0.01f, 0, 0);
//	else if (dxinput->KeyDown(DIK_D))camera->move(0.01f, 0, 0);
//	else if (dxinput->KeyDown(DIK_W))camera->move(0, 0, 0.01f);
//	else if (dxinput->KeyDown(DIK_S))camera->move(0, 0, -0.01f);
//
//	camera->rot(Camera::up, 0.01*dxinput->GetMouseX());
//	camera->rot(Camera::rig, 0.01*dxinput->GetMouseY());
//}
//
//void render() {
//	update();
//	d3dDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xffffffff, 1.0f, 0);
//	d3dDevice->BeginScene();
//	//D3DXMATRIX VP = matView*matProj;
//	D3DXMATRIX VP = camera->GetView() * camera->GetProj();
//	//teapot->DrawSubset(0);
//	D3DXVECTOR4 lightpos = {0, 30, -30 , 1};
//	eff->SetVector("lightpos", &lightpos);
//	eff->SetMatrix("ViewProjMat", &VP);
//	ani->Render();
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