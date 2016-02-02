#pragma once


#include"d3dutil.h"
#include"animation.h"
#include"typer.h"
#include"camera.h"
#include"inputsystem.h"
#include"Mesh.h"
#include"drawgraph.h"
#include"gui.h"

using namespace d3d;
using namespace std;

const int WID = 1200;
const int HEI = 900;

// gobal 
extern HINSTANCE ghInstance;
extern HWND ghwnd;

extern LPDIRECT3DDEVICE9 gdevice;
extern Camera *camera;
extern InputController *dxinput;
extern TYPER *typer;

// for draw 
extern ID3DXMesh *g_box, *g_ball;

// for coding
extern ifstream fin;
extern ofstream Log;


extern int pm, hasdelete, hasnew;
extern GUIwindow *curGUI;

#define keydown(x) dxinput->KeyDown(x)
#define keyup(x)  dxinput->KeyUp(x)



// ------------------init windows ----------------------
LRESULT CALLBACK winproc(HWND, UINT, WPARAM, LPARAM);
HWND WinInit(HINSTANCE hInstance, LPDIRECT3DDEVICE9 *d3dDevice);
void GameLoop(void(*render)(float dt));
// ---------------------d3d init device--------------
bool d3dInit(HWND hwnd, LPDIRECT3DDEVICE9 *d3dDevice);

//------------------ interface for gamemain ---------------
struct App {

	virtual void init();
	virtual void update(float dt);
	virtual void render();
	virtual void clear();
	virtual ~App() {} 
};

extern App *gapp;

// -------------------- gobal game loop --------------------------
void ginit();
void gupdate(float dt);
void gdisplay(float dt);
void gclear();

