#include"CharState.h"
#include"chars.h"

StateMgr::StateMgr(Chars *cs) : cs(cs)
{
	memset(m_state, 0, sizeof(m_state));
	m_state[CSstand] = new CharsStand(this);
	m_state[CSwalk] = new CharsWalk(this);
	m_state[CSevade] = new CharsEvade(this);
	m_state[CSbeated] = new CharsBeated(this);
	m_state[CSfindEnemy] = new CharsFindEnermy(this);
	m_state[CSattack] = new CharsAttack(this);
	
	m_curstate = m_state[CSstand];
}

StateMgr::~StateMgr()
{
	for (int i = 0; i < Nstate; ++i)
	{
		if (m_state[i]) delete m_state[i];
		m_state[i] = 0;
	}
}

void StateMgr::update(float dt)
{
	m_curstate->update(dt);
}

// ----------------------- CharsState ---------------------------- 
bool CharsState::ToStand()
{
	mgr->setState(CSstand);
	return 1;
}

bool CharsState::ToEvade()
{
	if (mgr->cs->evadetar) {
		mgr->setState(CSevade);
		return 1;
	}
	return 0;
}

bool CharsState::ToBeated()
{
	// 击退
	if (mgr->cs->beatDis > 0) {
		mgr->setState(CSbeated);
		return 1;
	}
	return 0;
}

bool CharsState::ToWalk()
{
	mgr->setState(CSwalk);
	return 1;
}


bool CharsState::ToFindEnermy()
{
	if (mgr->cs->enemy)
	{
		mgr->setState(CSfindEnemy);
		return 1;
	}
	return 0;
}

bool CharsState::ToAttack()
{
	mgr->setState(CSattack);
	return 1;
}





/// ---------------------- CharsStand --------------------
void CharsStand::update(float dt)
{
	Chars *cs = mgr->cs;

	if (ToBeated())  return;
	if (ToFindEnermy()) return;

	cs->m_mesh->Reset();
	if (rand() % 5 == 0)
	{
		cs->m_walkTar = D3DXVECTOR3(RandAB(-100, 100) / 10, 0, RandAB(-100, 100) / 10);
		cs->m_movespeed = g_movespeed;
		D3DXVec3Normalize(&cs->m_dir, &(cs->m_walkTar - cs->m_pos));

		mgr->setState(CSwalk);
	}

	

	
};


// ----------------------- CharsWalk ----------------------

void CharsWalk::update(float dt)
{
	Chars *cs = mgr->cs;

	if (ToBeated())  return;
	if (ToEvade()) return;
	if (ToFindEnermy()) return;


	if (D3DXVec3Length(&(cs->m_pos - cs->m_walkTar)) < 1)
	{
		mgr->setState(CSstand);
	}
	else
	{
		cs->m_pos += cs->m_movespeed * cs->m_dir * dt;
		cs->m_mesh->Display(dt);
	}
};


// --------------------------CharsEvade ----------------------------- 
void CharsEvade::update(float dt)
{
	Chars *cs = mgr->cs;

	if (ToBeated())  return;

	Chars *es = cs->evadetar;
	if (!es) return;

	// 前方有人就停
	mgr->setState(CSstand);
	cs->evadetar = 0;
}

// --------------------------CharsBeated ----------------------------- 

void CharsBeated::update(float dt){

	Chars *cs = mgr->cs;

	if (cs->beatDis > 0)
	{
		if (curframe == 1)
		{
			cs->m_dir = -cs->beatDir;
			cs->m_mesh->Reset();
			cs->m_mesh->InsMotion("Salute");
			curframe = 0;
		}
		else {
			// 击退
			D3DXVECTOR3 move = cs->beatDir * cs->m_movespeed * dt * 5;
			cs->m_pos += move;
			cs->beatDis -= D3DXVec3Length(&move);
			cs->m_mesh->Display(dt*1.5);
		}
	}
	else
	{
		curframe = 1;
		cs->m_mesh->InsMotion("Walk");
		mgr->setState(CSstand);
	}
}


// ---------------------- CharsFindEnermy ------------------------
void CharsFindEnermy::update(float dt)
{
	Chars *cs = mgr->cs;
	Chars *enermy = cs->enemy;
	if (D3DXVec3Length(&(cs->m_pos - enermy->m_pos)) < 2 * g_collideDis)
	{
		cs->enemy = 0;
		if (ToAttack()) return;
	} 
	else
	{
		if (ToBeated()) return;
		if (ToEvade()) return;
		cs->m_dir = enermy->m_pos - cs->m_pos;
		D3DXVec3Normalize(&cs->m_dir, &cs->m_dir);
		cs->m_pos += cs->m_dir * cs->m_movespeed *dt*3;
		cs->m_mesh->Display(dt*1.5);
	}
}


// ------------------------- CharsAttack-------------------------

void CharsAttack::update(float dt)
{
	--restframe;

	Chars *cs = mgr->cs;
	if (restframe == 2)
	{
		cs->m_mesh->Reset();
		cs->m_mesh->InsMotion("Aim");
		cs->m_mesh->Display(dt*2);

		// 添加消息
		CharsMsg msg;
		if(rand()%3!=0) msg.text = "捡肥皂吧!";
		else  msg.text = "你S啊?";
		msg.frame = 10;
		cs->AddMsg(msg);
	}
	else if (restframe == 1)
	{
		SkillTracer *sk = new SkillTracer;
		sk->caster = cs;
		sk->validDis = g_skillDis;
		sk->m_pos = cs->m_pos + D3DXVECTOR3(0, 1, 0) + cs->m_dir*0.5;
		D3DXVECTOR3 dir = cs->m_dir;
		D3DXVec3Normalize(&dir, &dir);
		sk->m_dir = dir;
		sk->speed = g_skillspeed;
		sk->m_skillmesh = new SkillMesh;
		g_skillcontrol->AddSkill(sk);
	}
	else if (restframe == 0) {
		restframe = 3;
		cs->m_mesh->InsMotion("Walk");
		ToStand();
	}
}
