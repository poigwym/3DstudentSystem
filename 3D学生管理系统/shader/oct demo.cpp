//
//#include"display.h"
//
//#include"oct.h"
//#include"drawgraph.h"
//
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
//
//
//extern ID3DXMesh *g_box;
//OCT *octtree;
//
//int N;
//float ballsize;
//D3DXVECTOR3 pos[111];
//
////#define BUG
//
//struct BHVOBJ : public BHV 
//{
//	ID3DXMesh *ball;
//	BHVOBJ(D3DXVECTOR3 pos, D3DXVECTOR3 box):BHV(pos, box)
//	{
//		D3DXCreateSphere(gdevice, 1.0f, 50, 50, &ball, 0);// 创建一个球体模型。
//	}
//
//	virtual void render() {
//		assert(ball != 0);
//		D3DXMATRIX world, scale;
//		D3DXMatrixTranslation(&world, m_pos.x, m_pos.y, m_pos.z);
//		D3DXMatrixScaling(&scale,ballsize, ballsize, ballsize);
//		world = scale*world;
//		gdevice->SetTransform(D3DTS_WORLD, &world);
//		ball->DrawSubset(0);
//	}
//};
//
////BHV *bhv[N];
//BHVOBJ *bhv[111];
//
//void  App::init() {
//
//	fin >> N;
//	fin >> ballsize;
//	srand(time(0));
//	
//	octtree = new OCT(D3DXVECTOR3(0,0,0), D3DXVECTOR3(10, 10, 10), 20, 10);
//
//	pos[0] = D3DXVECTOR3(0,0,0);
//	pos[1] = D3DXVECTOR3(10,10,10);
//	pos[2] = D3DXVECTOR3(-10, -10, -10);
//
//
//	for(int i=3;i<N;++i)
//	{
//		pos[i] = D3DXVECTOR3(RandAB(-10, 10), RandAB(-10, 10), RandAB(-10,10));
//	}
//
//#ifdef BUG
//	octtree->debugbuild();
//	MCOUT("build ok");
//#endif
//
//	for(int i=0;i<N;++i) 
//	{
//		//bhv[i] = new BHV(pos[i],D3DXVECTOR3(1,1,1));
//		bhv[i] = new BHVOBJ(pos[i],D3DXVECTOR3(ballsize/2, ballsize/2, ballsize/2));
//		octtree->Ins(bhv[i]);
//	}
//
//	D3DXCreateBox(gdevice, 1, 1, 1, &g_box, 0);
//
//
//
//	//gdevice->SetRenderState(D3DRS_LIGHTING, 0);
//}
//
//void App::update() {
//
//}
//
//void App::render() {
//
//
//	gdevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
//
//#ifdef BUG
//	octtree->debugoutput();
//#endif
//
//	octtree->outputframework();
//	octtree->outputobj();
//	
//
//}
//void  App::clear() {
//}
//
//
////入口函数
//int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lptCmdLine, int nCmd)
//{
//	ghInstance = hInstance;
//	ginit();
//	GameLoop(gdisplay);
//	gclear();
//	return 0;
//}