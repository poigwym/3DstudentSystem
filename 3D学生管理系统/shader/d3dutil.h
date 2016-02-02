#pragma once


#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<vector>
#include<algorithm>
#include<queue>
#include<stack>
#include<set>
#include<map>
#include<utility>
#include<fstream>
#include<sstream>
#include<cassert>

#include<Windows.h>
#include<tchar.h>
#include<ctime>
#include<d3dx9.h>
#include<d3d9.h>

using namespace std;

#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib, "Winmm.lib")


#define MCOUT(x)  MessageBox(0, x, 0, 0)
#define FUCK MessageBox(0, "fuck", 0, 0)
namespace d3d {
	typedef D3DXVECTOR4 vector4;
	typedef D3DXVECTOR3 vector3;

	

	#define INF 1e9

	#define RELEASE(x) { if(x) (x)->Release(); x=0; }
	#define DELETE(x) { if(x) delete x; x=0;}	
	#define DELETEARRAY(x) { if(x) delete[] x; x=0; } 

	template<class T> 
	T MinMax(T a, T b, T v) { return max(b, min(a,b)); }

	// ------------------- Colors ------------------------
	const D3DXCOLOR      WHITE(D3DCOLOR_XRGB(255, 255, 255));
	const D3DXCOLOR      BLACK(D3DCOLOR_XRGB(0, 0, 0));
	const D3DXCOLOR        RED(D3DCOLOR_XRGB(255, 0, 0));
	const D3DXCOLOR      GREEN(D3DCOLOR_XRGB(0, 255, 0));
	const D3DXCOLOR       BLUE(D3DCOLOR_XRGB(0, 0, 255));
	const D3DXCOLOR     YELLOW(D3DCOLOR_XRGB(255, 255, 0));
	const D3DXCOLOR       CYAN(D3DCOLOR_XRGB(0, 255, 255));
	const D3DXCOLOR    MAGENTA(D3DCOLOR_XRGB(255, 0, 255));

	//--------------------- lights ------------------------
	//

	D3DLIGHT9 InitDirectionalLight(D3DXVECTOR3* direction, D3DXCOLOR* color);
	D3DLIGHT9 InitPointLight(D3DXVECTOR3* position, D3DXCOLOR* color);
	D3DLIGHT9 InitSpotLight(D3DXVECTOR3* position, D3DXVECTOR3* direction, D3DXCOLOR* color);

	// ------------------------- Materials-------------------
	//

	D3DMATERIAL9 InitMtrl(D3DXCOLOR a, D3DXCOLOR d, D3DXCOLOR s, D3DXCOLOR e, float p);

	const D3DMATERIAL9 WHITE_MTRL = InitMtrl(WHITE, WHITE, WHITE, BLACK, 2.0f);
	const D3DMATERIAL9 RED_MTRL = InitMtrl(RED, RED, RED, BLACK, 2.0f);
	const D3DMATERIAL9 GREEN_MTRL = InitMtrl(GREEN, GREEN, GREEN, BLACK, 2.0f);
	const D3DMATERIAL9 BLUE_MTRL = InitMtrl(BLUE, BLUE, BLUE, BLACK, 2.0f);
	const D3DMATERIAL9 YELLOW_MTRL = InitMtrl(YELLOW, YELLOW, YELLOW, BLACK, 2.0f);


	

}