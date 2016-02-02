//
//#include"display.h"
//#include<ctime>
//#include"OBB.h"
//#define Deg2Rnd(x) D3DX_PI / 180 * (x)
//
//#define keydown(x) dxinput->KeyDown(x)
//#define keyup(x)  dxinput->KeyUp(x)
//extern HINSTANCE ghInstance;
//extern LPDIRECT3DDEVICE9 gdevice;
//extern Camera *camera;
//extern InputController *dxinput;
//extern TYPER *typer;
//extern ifstream fin;
//App *gapp = new App;				//  interface
//
//
//ID3DXMesh *teapot;
//
//fstream fout("output.txt", ios::ate);
//
//
//OBB *obb[2];
//vector3D pos[2];
//vector3D Size[2];
//void  App::init() {
//
//	D3DXCreateTeapot(gdevice, &teapot, 0);
//	for(int i=0;i<2;++i) 
//	{
//		obb[i] = new OBB;
//		fin >> pos[i].x >> pos[i].y >> pos[i].z;
//		fin >> Size[i].x >> Size[i].y >> Size[i].z;
//		obb[i]->SetSize(Size[i]);
//		obb[i]->m_pos = pos[i];
//	}
//}
//
//void App::update() {
//	if(keydown(DIK_LEFT)) obb[0]->move(-0.05,0,0);
//	else if(keydown(DIK_RIGHT)) obb[0]->move(0.05,0,0);
//	if (keydown(DIK_DOWN)) obb[0]->move(0,-0.05,0);
//	else if (keydown(DIK_UP)) obb[0]->move(0,0.05,0);
//}
//
//D3DXQUATERNION rot[2];
//float press;
//void App::render() {
//
//	if(keydown(DIK_SPACE) && press < 0.0001) {
//		rot[0] = D3DXQUATERNION(rand() % 1000 - 500.0f, rand() % 1000 - 500.0f, rand() % 1000 - 500.0f, rand() % 1000 - 500.0f);
//		rot[1] = D3DXQUATERNION(rand() % 1000 - 500.0f, rand() % 1000 - 500.0f, rand() % 1000 - 500.0f, rand() % 1000 - 500.0f);
//		D3DXQuaternionNormalize(rot, rot);
//		D3DXQuaternionNormalize(rot+1, rot+1);
//	}
//	float dt = 0.001;
//	press -= dt;
//	int i,j;
//	for(i=0;i<1;++i) 
//	{
//		obb[i]->m_dir += dt*rot[i];
//		D3DXQuaternionNormalize(&obb[i]->m_dir, &obb[i]->m_dir);
//	}
//	for(i=0;i<2;++i)
//		obb[i]->render();
//	if (isCollision(*obb[0], *obb[1]))
//		typer->render("!!!!!", 50, 50);
//	
//		
//}
//void  App::clear() {
//	RELEASE(teapot);
//}
