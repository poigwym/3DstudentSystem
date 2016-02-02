//
//#include"d3dutil.h"
//#include"animation.h"
//#include"camera.h"
//#include"inputsystem.h"
//using namespace d3d;
//
//using namespace std;
//#define FUCK  MessageBox(0, "fuck",0,0)
//
//HWND ghwnd;
//LPDIRECT3DDEVICE9 d3dDevice;
//Camera *camera;
//InputController *dxinput;
//ID3DXMesh  *teapot;
//
//char *Xname = "lxq.X";
//SkinMesh *staticanimation;
//
//struct Shader {
//	LPDIRECT3DDEVICE9 d3dDevice;
//	ID3DXConstantTable *ConstTable;
//
//	Shader() { memset(this, 0, sizeof(*this)); }
//	Shader(LPDIRECT3DDEVICE9 _d3dDevice) : d3dDevice(_d3dDevice) {}
//	virtual ~Shader() {}
//	virtual void init() {}
//	virtual void render() {}
//};
//
//
//
//
//struct VertexShader : public Shader {
//
//	IDirect3DVertexShader9 *vs;
//	D3DXHANDLE  hViewProjMat, hWorldViewMat;
//	D3DXHANDLE hlightpos;
//	VertexShader() { }
//	VertexShader(LPDIRECT3DDEVICE9 _d3dDevice) :Shader(_d3dDevice) {}
//	virtual ~VertexShader() {
//		RELEASE(vs);
//	}
//	virtual void init() {
//		HRESULT hr;
//		ID3DXBuffer *shader = 0;
//		ID3DXBuffer *errorbuffer = 0;
//		
//		// vertexshader 入口函数
//		//编译， 创建缓存, 常量表
//		hr = D3DXCompileShaderFromFile("aa.hlsl",
//			0, 0, "VS_Main", "vs_2_0", D3DXSHADER_DEBUG,
//			&shader, &errorbuffer, &ConstTable);
//		if (FAILED(hr)) {
//			MessageBox(0,(char*) errorbuffer->GetBufferPointer() , 0, 0);
//			return;
//		}
//
//		// 创建 vertex shader
//		hr = d3dDevice->CreateVertexShader((DWORD*)shader->GetBufferPointer(), &vs);
//		if (FAILED(hr)) {
//			MessageBox(0, "create vs fail", 0, 0);
//			return;
//		}
//		RELEASE(shader);
//
//		ConstTable->SetDefaults(d3dDevice);
//
//		hViewProjMat = ConstTable->GetConstantByName(0, "WorldViewProjMat");
//		hlightpos = ConstTable->GetConstantByName(0, "lightpos");
//
//		
//	}
//	virtual void render() {
//		// 矩阵放到顶点着色器
//		D3DXMATRIX viewproj;
//		viewproj = camera->GetView()*camera-> GetProj();
//		ConstTable->SetMatrix(d3dDevice, hViewProjMat, &viewproj);
//		static float dd = 0;
//		dd+= D3DX_PI*0.001;
//		D3DXVECTOR3 lightpos = D3DXVECTOR3(50, 100, 0), tmp;
//		D3DXMATRIX rot;
//		D3DXMatrixRotationY(&rot, dd);
//		D3DXVec3TransformCoord(&tmp, &lightpos, &rot);
//		D3DXVECTOR4 lightpos_ = D3DXVECTOR4(tmp.x, tmp.y, tmp.z, 1);
//		ConstTable->SetVector(d3dDevice, hlightpos, &lightpos_);
//		// output
//		d3dDevice->SetRenderState(D3DRS_LIGHTING, 1);    // 开光照
//		
//		// vertex shader
//		d3dDevice->SetVertexShader(vs);
//	}
//};
//
//
//// -------------------------- pixel
//struct PixelShader : public Shader {
//
//	IDirect3DPixelShader9 *ps;
//	PixelShader() { }
//	PixelShader(LPDIRECT3DDEVICE9 _d3dDevice) :Shader(_d3dDevice) {}
//	virtual ~PixelShader() {
//		RELEASE(ps);
//	}
//	virtual void init() {
//		HRESULT hr;
//		ID3DXBuffer *shader = 0;
//		ID3DXBuffer *errorbuffer = 0;
//
//		// vertexshader 入口函数
//		//编译， 创建缓存, 常量表
//		hr = D3DXCompileShaderFromFile("bb.hlsl",
//			0, 0, "PS_Main", "ps_2_0", D3DXSHADER_DEBUG,
//			&shader, &errorbuffer, &ConstTable);
//		if (FAILED(hr)) {
//			MessageBox(0, (char*)errorbuffer->GetBufferPointer(), 0, 0);
//			return;
//		}
//
//		if(!d3dDevice) return;
//		// 创建 vertex shader
//		hr = d3dDevice->CreatePixelShader((DWORD*)shader->GetBufferPointer(), &ps);
//		if (FAILED(hr)) {
//			MessageBox(0, "create ps fail", 0, 0);
//			return;
//		}
//		RELEASE(shader);
//
//		ConstTable->SetDefaults(d3dDevice);
//
//	}
//	virtual void render() {
//		d3dDevice->SetPixelShader(ps);
//	}
//};
//
//
//VertexShader *vs;
//PixelShader *ps;
//
//void init() {
//	vs = new VertexShader(d3dDevice);
//	vs->init();
//	ps = new PixelShader(d3dDevice);
//	ps->init();
//
//	camera = new Camera(d3dDevice, WID, HEI);
//	camera->SetEye(0,0,-50);
//	camera->SetTar(0,0,0);
//	camera->SetView();
//	camera->SetProj();
//	camera->SetViewport();
//
//	D3DXCreateTeapot(d3dDevice, &teapot, 0);
//
//	
//	staticanimation = new SkinMesh(Xname, d3dDevice);
//	D3DVIEWPORT9 vp = { 0, 0, WID, HEI, 0, 1 };
//	d3dDevice->SetViewport(&vp);
//}
//
//void update() {
//	dxinput->update();
//	if(dxinput->KeyDown(DIK_A)) camera->move(-0.1f, 0, 0);
//	else if(dxinput->KeyDown(DIK_D))camera->move(0.1f,0,0);
//	else if(dxinput->KeyDown(DIK_W))camera->move(0,0,0.1f);
//	else if(dxinput->KeyDown(DIK_S))camera->move(0,0,-0.1f);
//	
//	camera->rot(Camera::up, 0.01*dxinput->GetMouseX());
//	camera->rot(Camera::rig, 0.01*dxinput->GetMouseY());
//}
//
//void render() {
//	update();
//	d3dDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xffffffff, 1.0f, 0);
//	d3dDevice->BeginScene();
//
//	vs->render();
//	ps->render();
//	camera->SetView();
//	d3dDevice->SetTransform(D3DTS_VIEW, &camera->GetView());
//	d3dDevice->SetTransform(D3DTS_PROJECTION, &camera->GetProj());
//	//teapot->DrawSubset(0);
//	staticanimation->Render();
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
//  //入口函数
//int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lptCmdLine, int nCmd)
//{
//	if (!(ghwnd=WinInit(hInstance, &d3dDevice))) {
//		return 0;
//	}
//	// input
//	dxinput = new InputController(hInstance, ghwnd, 0);
//	
//	init();
//
//	GameLoop(render);
//
//	return 0;
//}