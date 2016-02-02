
#include"flock.h"

extern ofstream Log;

// default
float MaxVel = 0.05;
float MaxX = 0.05;
float NeighbourDis = 5;
int BoxX=20, BoxY=20, BoxZ=20;  
float SepDis = 1;
D3DXVECTOR3  centerpoint(0, 0, 0);

Boid::Boid() 
{
	m_pos = D3DXVECTOR3(rand()% BoxX , rand()% BoxY , rand()% BoxZ);
	m_vel= D3DXVECTOR3(rand()%10*MaxVel+ MaxVel, rand()%10* MaxVel+ MaxVel, rand()%10* MaxVel+ MaxVel);
}

Boid::~Boid()
{
}

void Boid::GetNeibours() 
{
	m_neibour.clear();
	for(int i=0;i<flock->size();++i) 
		if((*flock)[i] != this && D3DXVec3Length(&((*flock)[i]->m_pos - m_pos)) < NeighbourDis)
			m_neibour.push_back((*flock)[i]);
}

void Boid::FindNearest() {
	m_nearest = 0;
	if (m_neibour.size())
	{
		float dis;
		for (int i = 0;i<m_neibour.size();++i) {
			float len = D3DXVec3Length(&(m_pos - m_neibour[i]->m_pos));
			if (i == 0 || len < dis) {
				dis = len;
				m_nearest = m_neibour[i];
			}
		}
	}
}


void Boid::FlockIt() 
{
	GetNeibours();
	FindNearest();
	D3DXVECTOR3 acc(0,0,0);
	acc += ToCenter() + KeepDistance() + MatchHeading() +ToSteerPoint() + Adjust();
	acc = SetMagnitudeOfVector(acc, 3);
	m_vel += acc;
	m_vel = SetMagnitudeOfVector(m_vel, 1.5);
	m_oldpos = m_pos;
	m_pos += m_vel*0.1;
	m_pos.x = max(-BoxX, min(BoxX, m_pos.x));
	m_pos.y = max(-BoxY, min(m_pos.y, BoxY));
	m_pos.z = max(-BoxZ, min(m_pos.z, BoxZ));
	m_pos.y = d3d::MinMax(0.0f, 1.0f, m_pos.y);
}


D3DXVECTOR3 Boid::ToCenter()
{
	D3DXVECTOR3 center(0,0,0);
	if(m_neibour.size())  {
		for(int i=0;i<m_neibour.size();++i)
			center += m_neibour[i]->m_pos;
		center/=(int)m_neibour.size();
		center = center - m_pos;
		center = SetMagnitudeOfVector(center, urgence);
	} 
	return center;
}

D3DXVECTOR3 Boid::KeepDistance() {
	D3DXVECTOR3 separate(0, 0, 0);
	for(int i=0;i<m_neibour.size();++i) {
		D3DXVECTOR3 sep = m_pos - m_neibour[i]->m_pos;
		float dis = D3DXVec3Length(&sep);
		if(dis < SepDis)
			separate += SetMagnitudeOfVector(sep, 1.0 - dis / SepDis);
	}
	return separate;
}

D3DXVECTOR3 Boid::MatchHeading() {
	D3DXVECTOR3 heading(0, 0, 0);
		if(m_neibour.size()) {
		for(int i=0;i<m_neibour.size();++i) 
			heading += m_neibour[i]->m_vel;
		heading /= m_neibour.size();
		heading = SetMagnitudeOfVector(heading, urgence);
	}
	return heading;
}

D3DXVECTOR3 Boid::ToSteerPoint() 
{
	D3DXVECTOR3 steer = centerpoint - m_pos;
	return  SetMagnitudeOfVector(steer, urgence);
}

D3DXVECTOR3 Boid::Adjust() {
	// adjust a bit
	D3DXVECTOR3 adjust = D3DXVECTOR3(rand()%20*MaxVel + MaxVel, rand()%20*MaxVel + MaxVel, rand()%20* MaxVel + MaxVel);
	return SetMagnitudeOfVector(adjust, urgence);
}

D3DXVECTOR3 Boid::SetMagnitudeOfVector(D3DXVECTOR3 &v, float m) {
	D3DXVec3Normalize(&v,&v);
	return v*m;
}

void Boid::Render() 
{
}

// ---------------- Flock ---------------
void Flock::InsBoid(Boid *b)
{
	m_boids.push_back(b);
	b->flock = &m_boids;
}


void Flock::FlockUp() 
{
	for(int i=0;i<m_boids.size();++i) 
		m_boids[i]->FlockIt();
}


void Flock::Render()
{
	for(int i=0;i<m_boids.size();++i) 
		m_boids[i]->Render();
}