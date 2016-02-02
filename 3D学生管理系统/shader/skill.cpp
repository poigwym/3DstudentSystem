


#include"skill.h"

void SkillController::AddSkill(SkillTracer *s)
{
	m_skills.push_back(s);
}

void SkillController::Update(float dt)
{
	for(Sit it = m_skills.begin(); it != m_skills.end(); )
	{
		SkillTracer *s = *it;
		s->m_pos += dt * s->m_dir * s->speed;
		s->validDis -= dt * s->speed;
		if(s->validDis <= 0)
		{
			DELETE(*it);
			it = m_skills.erase(it);
		}
		else 
			++it;
	}
}


void SkillController::Render()
{
	for (Sit it = m_skills.begin(); it != m_skills.end(); ++it)
	{
		(*it)->Render();
	}
}
