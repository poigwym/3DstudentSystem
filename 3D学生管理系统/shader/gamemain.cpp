#include"gamemain.h"
#include"gui.h"



// for game
CharsController *g_charsControl;
SkillController  *g_skillcontrol;
GameB gameb;



// gobal magnity
float g_defaultHp, g_defaultMp;
float g_rolesize;
float g_movespeed, g_skillspeed;
float g_attackpower;
float g_skillDis;
float g_collideDis;
float g_animationspeed;
int n;
Chars *player, *monster;

// model
char *rolefile = "meshes/soldier/soldier.X";
// animation track order
//Salute
//Aim
//Still
//Walk
Mesh *terrain;
char *terrainfile = "floor.X";
LPDIRECT3DTEXTURE9 skilltexture;
char *skilltextureFile = "picture/bulleteffect.png";


// 全局光
D3DXVECTOR4 g_lightpos = D3DXVECTOR4(0, 10, 0, 1);

// 对话框
GUIbutton *g_dialog;
char dialogfile[] = "GUIMedia/button.png";
char *rolename[] = { "猪挺?", "猪头?", "SB?" };
const int Nname = sizeof(rolename) / sizeof(char*);
float dialogX = 200, dialogY = 50;

void GameB::init()
{

	srand(time(0));

	g_charsControl = new CharsController;
	g_skillcontrol = new SkillController;

	// gobal input

	fin >> g_defaultHp >> g_defaultMp;
	fin >> g_movespeed >> g_skillspeed;
	fin >> g_attackpower;
	fin >> g_skillDis >> g_collideDis;
	fin >> g_animationspeed;
	fin >> n >> g_rolesize;


	// new monster

	for (int i = 0; i<n; ++i)  {
		monster = new Chars;
		monster->type = CTmonster;
		monster->m_pos = D3DXVECTOR3(i, 0, i);
		monster->m_mesh = new SkinMesh(rolefile);
		monster->AddBox(Cbox(g_rolesize, g_rolesize, g_rolesize));
		monster->m_mesh->InsMotion("Walk");
		monster->m_mesh->SetTrackSpeed(0, g_animationspeed);

		g_charsControl->insChars(monster);
	}


	// 地形网格
	terrain = new Mesh("meshes/terrain/", terrainfile);

	// skill
	D3DXCreateTextureFromFile(gdevice, skilltextureFile, &skilltexture);

	// 对话框
	g_dialog = new GUIbutton(gdevice, dialogX, dialogY, "", "");
	g_dialog->setBounding(dialogfile);
	g_dialog->setVis(0);
}

void GameB::update(float dt)
{

	g_charsControl->Update(dt);
	g_skillcontrol->Update(dt);

	for (CharsController::Cit it = g_charsControl->m_chars.begin(); it != g_charsControl->m_chars.end(); ++it)
	{
		(*it)->m_pos = TerrainTrace((*it)->m_pos, terrain);
	}


	// 旋转camera
	D3DXVECTOR3 cpos;
	camera->GetEye(&cpos.x, &cpos.y, &cpos.z);
	D3DXMATRIX rot;
	D3DXMatrixRotationY(&rot, dt*0.3);
	D3DXVec3TransformCoord(&cpos, &cpos, &rot);
	camera->SetEye(cpos.x, cpos.y, cpos.z);
	camera->SetTar(0, 0, 0);

	g_lightpos = D3DXVECTOR4(cpos.x, cpos.y, cpos.z, 1);
}

void GameB::render()
{

	// render terrain
	D3DXMATRIX world;
	D3DXMatrixIdentity(&world);
	gdevice->SetTransform(D3DTS_WORLD, &world);
	terrain->render();


	// set camera
	//render animation
	D3DXMATRIX VP = camera->GetView() * (camera->GetProj());
	gAnimationEffect->SetVector("lightpos", &g_lightpos);
	gAnimationEffect->SetMatrix("ViewProjMat", &VP);

	// render chars
	g_charsControl->Render();
	// render dialog
	int j = 0;
	for (auto i = g_charsControl->m_chars.begin(); i != g_charsControl->m_chars.end(); ++i)
	{
		Chars *cs = *i;

		D3DXVECTOR3 pos2d;
		D3DXVec3TransformCoord(&pos2d, &cs->m_pos, &VP);
		pos2d.x = (1 + pos2d.x)*WID / 2;
		pos2d.y = (1 - pos2d.y)*HEI / 2;
		g_dialog->setX(pos2d.x);
		g_dialog->setY(pos2d.y);
		g_dialog->setVis(1);
		g_dialog->setButtonText(rolename[j % Nname]);
		g_dialog->OnRender();
		++j;

		POINT o;
		o.x = pos2d.x; o.y = pos2d.y;
		if (!cs->m_MsgQue.empty()) {
			CharsMsg &msg = cs->m_MsgQue.front();
			if (--msg.frame == 0)
				cs->m_MsgQue.pop();
			float lx = pos2d.x - 2 * dialogX, ly = pos2d.y - 2 * dialogY;
			g_dialog->setX(lx);
			g_dialog->setY(ly);
			g_dialog->setButtonText(msg.text);
			g_dialog->OnRender();
			POINT a, b;
			a.x = lx+15; a.y = ly + dialogY -5;
			b.x = lx - 15 + dialogX; b.y = ly + dialogY - 5;
			drawline2D(o, a);
			drawline2D(o, b);
		}

		g_dialog->setVis(0);
	}
	

	// render skill
	g_skillcontrol->Render();


	
}

void GameB::clear()
{
}
