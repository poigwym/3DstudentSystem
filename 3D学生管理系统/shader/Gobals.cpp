
#include"Gobals.h"

// gobal 
HINSTANCE ghInstance;
HWND ghwnd;

LPDIRECT3DDEVICE9 gdevice;
Camera *camera;
InputController *dxinput;
TYPER *typer;

// for draw 
ID3DXMesh *g_box, *g_ball;


// for coding
ifstream fin("input.txt", ios::in);
ofstream Log("output.txt", ios::ate);



int pm = 0;
int hasdelete = 1;
int hasnew = 0;

#define  SOLIDcamera


// ----------------- init windows -------------------------
HWND WinInit(HINSTANCE hInstance, LPDIRECT3DDEVICE9 *d3dDevice) {
	WNDCLASSEX wnd;
	wnd.cbClsExtra = 0;
	wnd.cbSize = sizeof(wnd);
	wnd.cbWndExtra = 0;
	wnd.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wnd.hCursor = LoadCursor(NULL, IDC_ARROW);
	wnd.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wnd.hIconSm = wnd.hIcon;
	wnd.hInstance = hInstance;
	wnd.lpfnWndProc = winproc;						// 窗口过程
	wnd.lpszClassName = TEXT("d3d");				// 注册名    窗口类名
	wnd.lpszMenuName = NULL;
	wnd.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClassEx(&wnd);
	// 创建窗口
	HWND hwnd = CreateWindow(TEXT("d3d"), TEXT("学生管理系统也能3D???"), WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, 0);
	if (NULL == hwnd) return 0;
	ShowWindow(hwnd, SW_SHOWDEFAULT);
	UpdateWindow(hwnd);
	MoveWindow(hwnd, 0, 0, WID, HEI, 1);

	// init d3d
	if (!d3dInit(hwnd, d3dDevice)) return 0;
	return hwnd;
}

void GameLoop(void(*display)(float dt))
{
	MSG msg;
	while (1) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT) break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			static float tnow = GetTickCount()*0.001, tpre = tnow;
			tnow = GetTickCount()*0.001;
			if (tnow - tpre > 0.05) {
				display(tnow - tpre);
				tpre = tnow;
			}
		}
	}
}

//===============窗口过程====================  
LRESULT CALLBACK winproc(HWND hwnd, UINT imsg, WPARAM wparam, LPARAM lparam) {
	HDC hdc;
	switch (imsg)
	{
	case WM_MOUSEMOVE: {
											 break;
	}
	case WM_LBUTTONDOWN: {
												 int aa = 1;
												 break;
	}

	case WM_KEYDOWN:
	
		switch (wparam) {
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	if (curGUI) {
		curGUI->ProcessMSG(imsg, wparam, lparam);
		pm = 1;
	}
	return DefWindowProc(hwnd, imsg, wparam, lparam);
}

// -----------------------init d3d -------------------
bool d3dInit(HWND hwnd, LPDIRECT3DDEVICE9 *d3dDevice) {
	//1创建d3d接口   
	LPDIRECT3D9 pd3d = 0;
	if (NULL == (pd3d = Direct3DCreate9(D3D_SDK_VERSION)))    //初始化Direct3D接口对象，并进行DirectX版本协商
		return 0;
	//2提取硬件设备信息
	D3DCAPS9 caps;
	int vp = 0;
	if (FAILED(pd3d->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps)))
		return 0;
	if (caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;   //支持硬件顶点运算，我们就采用硬件顶点运算，妥妥的
	else
		vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING; //不支持硬件顶点运算，无奈只好采用软件顶点运算

																							//3填D3DPRESENT_PARAMETERS信息
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.BackBufferWidth = 0;
	d3dpp.BackBufferHeight = 0;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dpp.BackBufferCount = 1;
	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality = 0;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = hwnd;
	d3dpp.Windowed = true;
	d3dpp.EnableAutoDepthStencil = true;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	d3dpp.Flags = 0;
	d3dpp.FullScreen_RefreshRateInHz = 0;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	//4创建设备
	if (FAILED(pd3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hwnd, vp, &d3dpp, d3dDevice)))
		return 0;

	RELEASE(pd3d); //LPDIRECT3D9接口对象的使命完成，我们将其释掉
	return 1;
}



//#define SolidCamera
float cameraspeed;
void ginit() {
	ghwnd = WinInit(ghInstance, &gdevice);

	fin.seekg(0, ios::beg);


	// camera
	camera = new Camera(gdevice, WID, HEI);
	float ex, ey, ez, lx, ly, lz;
	fin >> ex >> ey >> ez >> lx >> ly >> lz;
	fin >> cameraspeed;
	camera->Update(D3DXVECTOR3(ex, ey, ez), D3DXVECTOR3(lx, ly, lz));



	// input
	dxinput = new InputController(ghInstance, ghwnd, 0);

	// string typer
	typer = new TYPER(gdevice, WID, HEI ,50,50);


	// for draw graph
	ID3DXBuffer *adjbuf;
	D3DXCreateBox(gdevice, 1, 1, 1, &g_box, 0);
	D3DXCreateSphere(gdevice, 1, 50, 50, &g_ball, 0);




	// for coding
	gapp->init();

	gdevice->SetRenderState(D3DRS_LIGHTING, 0);
}



void gupdate(float dt) {
	dxinput->update();


#ifndef SOLIDcamera

	if (dxinput->KeyDown(DIK_A)) camera->move(-cameraspeed,0, 0);
	else if (dxinput->KeyDown(DIK_D))camera->move(cameraspeed, 0, 0);
	else if (dxinput->KeyDown(DIK_W))camera->move(0, 0, cameraspeed);
	else if (dxinput->KeyDown(DIK_S))camera->move(0, 0, -cameraspeed);

	camera->rot(Camera::up, 0.01*dxinput->GetMouseX());
	camera->rot(Camera::rig, 0.01*dxinput->GetMouseY());
#endif 

	gapp->update(dt);
}

void gdisplay(float dt) {
	gupdate(dt);

	gdevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xffffffff, 1.0f, 0);
	gdevice->BeginScene();

	gapp->render();


	gdevice->EndScene();
	gdevice->Present(0, 0, 0, 0);
}

void gclear() {
	RELEASE(gdevice);
	DELETE(camera);
	DELETE(dxinput);
	DELETE(typer);
	fin.close();
	gapp->clear();
}
