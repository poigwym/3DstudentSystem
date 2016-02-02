//
//
//
//
//#include"display.h"
//
//#include"crowd.h"
//#include"animation.h"
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
//
//
//ID3DXMesh *teapot;
//extern ID3DXEffect *gAnimationEffect;
//char *Xname= "meshes/soldier.X";
//char *terrainname = "floor.X";
//Crowd *crow;
//Mesh *terrain;
//int N;
//float modelesize;
//
//struct CrowdAnimation : public CrowdEntity
//{
//	static SkinMesh *mesh;
//	CrowdAnimation() {
//	}
//	virtual void Render()  {
//		D3DXVECTOR3 org = m_pos + D3DXVECTOR3(0.0f, 1000.0f, 0.0f);
//		D3DXVECTOR3 dir = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
//
//		BOOL Hit;
//		DWORD FaceIndex;
//		FLOAT U;
//		FLOAT V;
//		FLOAT Dist;
//
//		//Floor-ray intersection test
//		D3DXIntersect(terrain->m_pmesh, &org, &dir, &Hit, &FaceIndex, &U, &V, &Dist, NULL, NULL);
//
//		if (Hit)
//		{
//			//Adjust position accordingly to the floor height
//			m_pos.y = org.y - Dist;
//		}
//
//		D3DXMATRIX world, rotx, roty, rotz, scal;
//		//float ang = atan2(m_vel.z, m_vel.x);
//		float ang = atan2(m_vel.z, -m_vel.x) + D3DX_PI * 0.5f;
//		D3DXMatrixRotationY(&roty, ang);
//		D3DXMatrixTranslation(&world, m_pos.x, m_pos.y, m_pos.z);
//		D3DXMatrixScaling(&scal, modelesize, modelesize, modelesize);
//		world = scal*roty*world;
//		//gdevice->SetTransform(D3DTS_WORLD, &world);
//		mesh->Move(world);
//		mesh->Render();
//	}
//	static void init() {
//		mesh = new SkinMesh(Xname);
//		vector<string> animname;
//		mesh->extractAnim(animname);
//		mesh->InsMotion("Walk");
//	}
//	static void update() {
//		static float tnow=GetTickCount()*0.001, tpre = tnow;
//		tnow = GetTickCount()*0.001;
//		mesh->Display(tnow-tpre);
//		tpre = tnow;
//	}
//};
//SkinMesh* CrowdAnimation::mesh = 0;
//
//void  App::init() {
//	
//	CrowdAnimation::init();
//	D3DXCreateTeapot(gdevice, &teapot, 0);
//	crow = new Crowd;
//	fin >> N;
//	fin >> modelesize;
//	for(int i=0;i<N;++i) 
//		crow->InsCrowEntity(new CrowdAnimation);
//
//	terrain = new Mesh("meshes/terrain/",terrainname);
//	gdevice->SetRenderState(D3DRS_LIGHTING, 0);    // 开光照
//
//}
//
//void App::update() {
//
//	CrowdAnimation::update();
//	crow->UpdateCrowd();
//}
//
//void App::render() {
//
//		D3DXMATRIX world;
//		D3DXMatrixTranslation(&world, 0,0,0);
//		gdevice->SetTransform(D3DTS_WORLD, &world);
//	//teapot->DrawSubset(0); 
//		terrain->render();
//
//
//
//			D3DXMATRIX VP = camera->GetView() * (camera->GetProj());
//			D3DXVECTOR4 lightpos = D3DXVECTOR4(0, 30, -30 , 1 );
//			gAnimationEffect->SetVector("lightpos", &lightpos);
//			gAnimationEffect->SetMatrix("ViewProjMat", &VP);
//			crow->Render();
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