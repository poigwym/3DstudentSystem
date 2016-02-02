
#include"chars.h"



// character 


void Chars::Render()
{

	D3DXMATRIX world, dir;
	D3DXMatrixTranslation(&world, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixRotationY(&dir, atan2(m_dir.z, -m_dir.x) + D3DX_PI*0.5);
	world = dir*world;
	
	if(type == CTmonster) 
	{
		D3DXMATRIX scale;
		D3DXMatrixScaling(&scale, m_box.x, m_box.y, m_box.z);
		world = scale * world;
	}

	//  render mesh
	m_mesh->Move(world);
	m_mesh->Render();
	
	// render message
	//D3DXMATRIX VP;
	//if (camera)
		//VP = camera->GetView() * camera->GetProj();
	//if(!m_MsgQue.empty()) 
	//{
	//	//typer->render((m_MsgQue.front()->text).c_str(), 10, 10);
	//	 //render dialog
	//	CharsMsg *msg = m_MsgQue.front();
	//	m_MsgQue.pop();
	//	D3DXVECTOR3 pos2d;
	//	D3DXVec3TransformCoord(&pos2d, &m_pos, &VP);
	//	pos2d.x = (1 + pos2d.x)*WID / 2;
	//	pos2d.y = (1 - pos2d.y)*HEI / 2;
	//	typer->render(msg->text.c_str(), pos2d.x, pos2d.y);
	//	DELETE(msg);
	//}
}



void CharsController::Update(float dt)
{
	for (Cit it = m_chars.begin(); it != m_chars.end(); ++it)
		(*it)->m_statemgr->update(dt);



	// 角色回避
	// 前方是否有人
	for (Cit it = m_chars.begin(); it != m_chars.end(); ++it)
	{
		Chars *cs = (*it);
		StateType now = cs->m_statemgr->getCurstate()->getType();
		if (now != CSwalk && now != CSfindEnemy) continue;
		D3DXVECTOR3 facepos = cs->m_pos + cs->m_dir;
		for (Cit j = m_chars.begin(); j != m_chars.end(); ++j)
		{
			Chars *js = (*j);
			if (cs == js) continue;
			if (D3DXVec3Length(&(facepos - js->m_pos)) < g_collideDis)
			{
				cs->evadetar = js;
				break;
			}
		}
	}



	for (SkillController::Sit j = g_skillcontrol->m_skills.begin();
		j != g_skillcontrol->m_skills.end();)
	{
		bool iscollide = 0;

		SkillTracer *sk = *j;

		for (Cit i = m_chars.begin(); i != m_chars.end(); ++i)
		{
			Chars *cs = *i;
			if (sk->caster == cs)
				continue;
			if (isSkillCollideChars(sk, cs))
			{
				iscollide = 1;

				// 设置击退
				cs->beatDis = g_skillDis;
				cs->beatDir = sk->m_dir;
				D3DXVec3Normalize(&cs->beatDir, &cs->beatDir);
				// damage


				j = g_skillcontrol->m_skills.erase(j);
				break;
			}
		}
		if (iscollide) continue;
		++j;
	}


	// 搜敌
	for (Cit it = m_chars.begin(); it != m_chars.end(); ++it)
	{
		Chars *cs = (*it);
		StateType now = cs->m_statemgr->getCurstate()->getType();
		if (now == CSevade || now == CSbeated) continue;
		for (Cit j = m_chars.begin(); j != m_chars.end(); ++j)
		{
			Chars *js = (*j);
			if (cs == js) continue;
			// 1/3几率设为敌人
			if (rand() % 50 == 1)
			{
				cs->enemy = js;
				break;
			}
		}
	}

}
void CharsController::Render()
{
	for (Cit it = m_chars.begin(); it != m_chars.end(); ++it)
		(*it)->Render();
}
