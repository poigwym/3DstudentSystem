//
//
//#include"flock.h"
//#include"display.h"
//#include"Mesh.h"
//
//#define Deg2Rnd(x) D3DX_PI / 180 * (x)
//
//extern HINSTANCE ghInstance;
//extern LPDIRECT3DDEVICE9 gdevice;
//extern Camera *camera;
//extern InputController *dxinput;
//extern TYPER *typer;
//extern ifstream fin;
//App *gapp = new App;				//  interface
//ID3DXEffect *gAnimationEffect=0;
//ofstream Log("output.txt", ios::ate);
//ID3DXMesh *teapot;
//
////char *boidname = "boid.X";
//char *boidname = "soldier.X";
//Mesh *boidmesh;
//int N = 10;
//float size;
//Flock *flock;
//
//struct BoidMesh : public Boid
//{
//	Mesh *m_mesh;
//	BoidMesh() {
//		m_mesh = new Mesh(boidname);
//	}
//	virtual void Render() 
//	{
//		D3DXMATRIX world, rotx, roty, rotz,scal;
//		float ang = atan2(m_pos.z, m_pos.x);
//		D3DXMatrixRotationY(&roty, ang);
//		D3DXMatrixTranslation(&world, m_pos.x, m_pos.y, m_pos.z);
//		D3DXMatrixScaling(&scal, size, size, size);
//		world = roty*scal*world;
//		gdevice->SetTransform(D3DTS_WORLD, &world);
//		m_mesh->render();
//	}
//};
//
//
//void  App::init() {
//
//	fin >> N;
//	fin >> size;
//	D3DXCreateTeapot(gdevice, &teapot, 0);
//	boidmesh = new Mesh(boidname);
//	flock = new Flock;
//	for(int i=0;i<N;++i) 
//		flock->InsBoid(new BoidMesh);
//	gdevice->SetRenderState(D3DRS_LIGHTING, 0);    // 开光照
//}
//
//void App::update() {
//	flock->FlockUp();
//}
//
//void App::render() {
//
//	float px, py, pz;
//
//	D3DXMATRIX world;
//	D3DXMatrixTranslation(&world, 0,0,0);
//	gdevice->SetTransform(D3DTS_WORLD, &world);
//	teapot->DrawSubset(0);
//	flock->Render();
//}
//void  App::clear() {
//	RELEASE(teapot);
//}
//
//
////入口函数
//int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lptCmdLine, int nCmd)
//{
//	srand(time(0));
//	ghInstance = hInstance;
//	ginit();
//	GameLoop(gdisplay);
//	gclear();
//	return 0;
//}