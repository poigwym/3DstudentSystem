
#include"crowd.h"


float DisToSep = 2.0;
float DisToAccess = 1.0;

CrowdEntity::CrowdEntity() 
{
	m_pos = GetRandomLocation();
	m_tar = GetRandomLocation();
	while(m_tar == m_pos) 
		m_tar = GetRandomLocation();
	D3DXVec3Normalize(&m_vel, &m_pos);
	q = 0;
}

CrowdEntity::~CrowdEntity() 
{
	
}

void CrowdEntity::UpdateCrowd() 
{
	D3DXVECTOR3 totar = m_tar - m_pos;
	D3DXVECTOR3 acc(0,0,0);
	acc = totar*0.1 + KeepDis();
	acc = SetMagnitudeOfVector(acc, 0.1f);
	m_vel += acc;
	m_vel = SetMagnitudeOfVector(m_vel, 0.02);
	m_pos += m_vel;
	
	if( D3DXVec3Length(&(m_pos-m_tar)) < DisToAccess)		
	{
		m_tar = GetRandomLocation();
		D3DXVec3Normalize(&m_vel, &m_pos);
		while(m_tar == m_pos) 
			m_tar = GetRandomLocation();

	}
}


D3DXVECTOR3 CrowdEntity::KeepDis() 
{
	D3DXVECTOR3 avoid(0,0,0);
	for(Cit it = q->begin(); it!=q->end(); ++it) 
	{
		D3DXVECTOR3 toOther = m_pos - (*it)->m_pos;
		float dis = D3DXVec3Length(&toOther);
		if(dis < DisToSep) 
			avoid += SetMagnitudeOfVector(toOther, 1.0f-dis/DisToSep);
	} 
	return avoid;
}

D3DXVECTOR3 CrowdEntity::SetMagnitudeOfVector(D3DXVECTOR3 &v, float m) {
	D3DXVec3Normalize(&v, &v);
	return v*m;
}



// ---------------------- Crowd Control -----------------------

Crowd::Crowd() 
{
	q.clear();
}

Crowd::~Crowd() {
	for(int i=0;i<q.size();++i) 
		delete q[i];
}

void Crowd::InsCrowEntity(CrowdEntity *p) {
	q.push_back(p);
	p->q = &q;
}
void Crowd::UpdateCrowd() 
{

	for(int i=0;i<q.size();++i) 
		q[i]->UpdateCrowd();
}
