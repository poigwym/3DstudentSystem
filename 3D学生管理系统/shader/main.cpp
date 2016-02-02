
#include"Gobals.h"

#include"StudentApp.h"
#include"gamemain.h"

#define Deg2Rnd(x) D3DX_PI / 180 * (x)


App *gapp = new App;				//  interface


extern ofstream fout;
extern studentApp g_studentApp;
extern GameB gameb;

void  App::init() {
	g_studentApp.init();
	gameb.init();
}

void App::update(float dt) {
	g_studentApp.update();
	gameb.update(dt);
}

void App::render() {

	gameb.render();
	g_studentApp.render();

}

void  App::clear() {
	g_studentApp.clear();
	gameb.clear();
}


//Èë¿Úº¯Êý
int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lptCmdLine, int nCmd)
{
	srand(time(0));
	ghInstance = hInstance;
	ginit();
	GameLoop(gdisplay);
	gclear();
	return 0;
}