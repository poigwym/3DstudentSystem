#pragma once


#include"d3dutil.h"
#include"Gobals.h"
#include"functools.h"

#include"animation.h"
#include"CharState.h"
#include"skill.h"

using namespace std;

// input gobal
extern float g_defaultHp,g_defaultMp;
extern float g_rolesize;
extern float g_movespeed, g_skillspeed;
extern float g_attackpower;
extern float g_skillDis;
extern float g_collideDis;


extern SkillController* g_skillcontrol;
extern InputController *dxinput;
extern TYPER *typer;
extern Camera *camera;




// 角色类型
enum CharsType
{
	CTplayer = 0,
	CTmonster
};


struct CharsMsg 
{
	CharsMsg() { frame = 1; }
	string text;
	int frame;
};

struct Cbox {
	float x, y, z;
	Cbox(float x = 0, float y = 0, float z = 0) :x(x), y(y), z(z){} 
};


struct Chars 
{
	CharsType type;
	Cbox m_box;
	SkinMesh *m_mesh;
	StateMgr *m_statemgr;
	queue<CharsMsg> m_MsgQue;


	float hp, mp;
	float m_movespeed, m_skillspeed;
	float m_skillpower;
	D3DXVECTOR3 m_pos, m_dir;
	D3DXVECTOR3 m_walkTar;
	// 被击
	D3DXVECTOR3 beatDir;				// 被击方向
	float beatDis;							// 后退移动的距离


	// 回避
	Chars *evadetar;

	// 搜敌
	Chars *enemy;

	Chars() {
		hp=mp=0;
		m_movespeed = g_movespeed;
		m_skillspeed = g_skillspeed;
		m_skillpower = m_skillpower;
		m_pos = D3DXVECTOR3(0,0,0);
		m_dir = D3DXVECTOR3(0,0,-1);
		evadetar = 0;
		enemy = 0;
		beatDis = 0;
		m_statemgr = new StateMgr(this);
		m_mesh = 0;
	}

	void AddMsg(CharsMsg msg) { 
		m_MsgQue.push(msg);
	}
	void AddBox(Cbox b) { m_box = b; }
	void Render();
};



inline bool isSkillCollideChars(SkillTracer *sk, Chars *cs)
{
	float x = sk->m_pos.x - cs->m_pos.x;
	float y = sk->m_pos.y - cs->m_pos.y;
	float z = sk->m_pos.z - cs->m_pos.z;

	if (x >= cs->m_box.x || x < -cs->m_box.x ||
		y >= cs->m_box.y || y < -cs->m_box.y ||
		z > cs->m_box.z || z < -cs->m_box.z)
		return 0;
	return 1;
}


struct CharsController
{
	vector<Chars*> m_chars;
	typedef vector<Chars*>::iterator Cit;


	CharsController() {}
	~CharsController() {
		for (Cit it = m_chars.begin(); it != m_chars.end(); ++it)
			DELETE(*it);
	}
	void insChars(Chars *c) {
		m_chars.push_back(c);
	}
	// for games
	void Update(float dt);
	void Render();
};

