//
//
//
//
//#include"display.h"
//
//
//#include"crowd.h"
//#include"animation.h"
//#include"Mesh.h"
//#include"navigmesh.h"
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
//ID3DXMesh *teapot;
//extern ID3DXEffect *gAnimationEffect;
//char *Xname= "meshes/soldier.X";
//char *terrainname = "floor.X";
//
//extern ofstream Log;
//
//
//
//
//
//Mesh *terrain;
//NavigationMesh *navmesh;
//D3DXVECTOR3 pos[2];
//SkinMesh *anim[2];
//NavigationPath *obj;
//
//
//
//D3DXVECTOR3  TerrainTest(D3DXVECTOR3 pos)
//{
//	D3DXVECTOR3 org = pos + D3DXVECTOR3(0.0f, 1000.0f, 0.0f);
//	D3DXVECTOR3 dir = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
//
//	BOOL Hit;
//	DWORD FaceIndex;
//	FLOAT U;
//	FLOAT V;
//	FLOAT Dist;
//
//	//Floor-ray intersection test
//	D3DXIntersect(terrain->m_pmesh, &org, &dir, &Hit, &FaceIndex, &U, &V, &Dist, NULL, NULL);
//
//	if (Hit)
//		pos.y = org.y - Dist;
//	return pos;
//}
//
//
//
//void  App::init() {
//	
//	terrain = new Mesh("meshes/terrain/",terrainname);
//	navmesh = new NavigationMesh(terrain);
//	pos[0] = D3DXVECTOR3(-2,0, 0);
//	pos[1] = D3DXVECTOR3(2, 0, 0);
//	obj = new NavigationPath(ToP2D(pos[1]));
//
//
//	D3DXCreateTeapot(gdevice, &teapot, 0);
//
//	for(int i=0;i<2;++i)  {
//	  anim[i] = new SkinMesh(Xname);
//		vector<string> animname;
//		anim[i]->extractAnim(animname);
//		anim[i]->InsMotion("Walk");
//	}
//
//	gdevice->SetRenderState(D3DRS_LIGHTING, 0);    // 开光照
//}
//
//void App::update() {
//	if(keydown(DIK_LEFT)) pos[0].x -= 0.1;
//	if(keydown(DIK_RIGHT)) pos[0].x += 0.1;
//	if(keydown(DIK_UP)) pos[0].z += 0.1;
//	if(keydown(DIK_DOWN)) pos[0].z -= 0.1;
//
//
//	if(keydown(DIK_SPACE)) 
//		if(navmesh->FindPath(pos[1], pos[0])) 
//		{
//			//Log << " found  !!!!!! " << endl;
//			vector<point2D> &path = navmesh->m_path;
//			obj->setpath(path);    // init path
//			obj->setpos(ToP2D(pos[1]));
//		}
//
//
//	// A* path
//	obj->update();
//
//
//
//	// update animation
//	static float tnow = GetTickCount()*0.001, tpre = tnow;
//	tnow = GetTickCount()*0.001;
//
//	anim[0]->Display(tnow - tpre);
//	anim[1]->Display(tnow - tpre);
//	tpre = tnow;
//
//}
//
//void App::render() {
//
//	// terrain
//	D3DXMATRIX world;
//  D3DXMatrixIdentity(&world);
//	gdevice->SetTransform(D3DTS_WORLD, &world);
//	terrain->render();
//
//	// render animation
//	D3DXMATRIX VP = camera->GetView() * (camera->GetProj());
//	D3DXVECTOR4 lightpos = D3DXVECTOR4(0, 30, -30, 1);
//	gAnimationEffect->SetVector("lightpos", &lightpos);
//	gAnimationEffect->SetMatrix("ViewProjMat", &VP);
//
//	pos[0] = TerrainTest(pos[0]);
//	pos[1] = TerrainTest(D3DXVECTOR3(obj->m_pos.x, 0, obj->m_pos.y));
//	for(int i=0;i<2;++i) {
//		D3DXMatrixTranslation(&world, pos[i].x, pos[i].y, pos[i].z);
//		D3DXMATRIX rot;
//		D3DXMatrixRotationY(&rot, obj->GetRotateAng());
//		world = rot*world;
//		anim[i]->Move(world);
//		anim[i]->Render();
//	}
//		
//
//}
//void  App::clear() {
//
//	DELETE(anim[0]);
//	DELETE(anim[1]);
//	DELETE(terrain);
//	DELETE(obj);
//	DELETE(navmesh);
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