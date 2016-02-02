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
//char *Xname = "lxq.X";
//SkinMesh *ani;
//
//
//
//
//struct Shader {
//	LPDIRECT3DDEVICE9 d3dDevice;
//
//	Shader() { memset(this, 0, sizeof(*this)); }
//	Shader(LPDIRECT3DDEVICE9 _d3dDevice) : d3dDevice(_d3dDevice) {}
//	virtual ~Shader() {}
//	virtual void init() {}
//	virtual void render() {}
//};
//
//
//struct EffectShader : public Shader {
//	ID3DXEffect *es;
//	ID3DXBuffer *errorbuf;
//	D3DXHANDLE hW, hVP;
//		D3DXHANDLE hL;
//	EffectShader(LPDIRECT3DDEVICE9 d3dDevice, const char*filename):Shader(d3dDevice) {
//		if(FAILED(D3DXCreateEffectFromFile(d3dDevice, filename, 0, 0, 0, 0, &es, &errorbuf))) 
//		{
//			mout((char*)errorbuf->GetBufferPointer());
//			exit(1);
//			return;
//		}
//		hW = es->GetParameterBySemantic(0, "WORLD");
//		hVP = es->GetParameterBySemantic(0, "VIEWPROJ");
//		hL = es->GetParameterBySemantic(0, "LIGHTPOS");
//
//	}
//
//	void render() {
//		es->SetTechnique("Lighting");
//		es->SetTechnique("Shadow");
//		D3DXVECTOR4 lightpos = { 50, 50, 0, 1 };
//
//		es->SetVector(hL, &lightpos);
//		D3DXMATRIX viewproj, world;
//		D3DXMatrixIdentity(&world);
//		es->SetMatrix("WorldMat", &world);
//		viewproj = camera->GetView()*camera-> GetProj();
//		es->SetMatrix("ViewProjMat", &viewproj);
//	  UINT c;
//
//		es->Begin(&c, 0);
//		for(int i=0;i<c;++i) {
//			es->BeginPass(i);
//			es->CommitChanges();
//			teapot->DrawSubset(0);
//			ani->Render();
//			es->EndPass();
//		}
//		es->End();
//	}
//};
//
//EffectShader *es;
//void init() {
//	es = new EffectShader(d3dDevice, "eff.hlsl");
//
//	camera = new Camera(d3dDevice, WID, HEI);
//	camera->SetEye(0, 0, -50);
//	camera->SetTar(0, 0, 0);
//	camera->SetView();
//	camera->SetProj();
//	camera->SetViewport();
//
//	D3DXCreateTeapot(d3dDevice, &teapot, 0);
//		ani = new SkinMesh(Xname, d3dDevice);
//
//}
//
//void update() {
//	dxinput->update();
//	if (dxinput->KeyDown(DIK_A)) camera->move(-0.1f, 0, 0);
//	else if (dxinput->KeyDown(DIK_D))camera->move(0.1f, 0, 0);
//	else if (dxinput->KeyDown(DIK_W))camera->move(0, 0, 0.1f);
//	else if (dxinput->KeyDown(DIK_S))camera->move(0, 0, -0.1f);
//
//	camera->rot(Camera::up, 0.01*dxinput->GetMouseX());
//	camera->rot(Camera::rig, 0.01*dxinput->GetMouseY());
//}
//
//void render() {
//	update();
//	d3dDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xff00ffff, 1.0f, 0);
//	d3dDevice->BeginScene();
//
//	teapot->DrawSubset(0);
//	es->render();
//
//	d3dDevice->EndScene();
//	d3dDevice->Present(0, 0, 0, 0);
//}
//
//
//void clear() {
//
//	RELEASE(d3dDevice);
//	DELETE(camera);
//	DELETE(dxinput);
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
//
//	return 0;
//}