#pragma once

#include"d3dutil.h"
struct Boid 
{
	D3DXVECTOR3 m_pos, m_oldpos, m_vel;
	Boid();
	~Boid();

	vector<Boid*> *flock;
	vector<Boid*> m_neibour;
	Boid *m_nearest;

	void GetNeibours();
	void FindNearest();
	void FlockIt();
	D3DXVECTOR3 ToCenter();			 // from center
	D3DXVECTOR3 KeepDistance();  // keep distance from nearest one
	D3DXVECTOR3 MatchHeading();  // keep heading from the group
	D3DXVECTOR3 ToSteerPoint();
	D3DXVECTOR3 SetMagnitudeOfVector(D3DXVECTOR3 &v, float m);  
	D3DXVECTOR3 Adjust();					// adjust  a bit..
	virtual void Render();
};

const float urgence = 0.1;
extern D3DXVECTOR3  centerpoint;
extern float MaxVel ;
extern float MaxX ;
extern float NeighbourDis ;
extern int BoxX, BoxY, BoxZ;
extern float SepDis;
extern ifstream fin;

struct Flock 
{
	Flock() {
		m_boids.clear(); 
	}
	~Flock() {
		for(int i=0;i<m_boids.size();++i) delete m_boids[i];
	}
	vector<Boid*> m_boids;

	void InsBoid(Boid *b);
	void FlockUp();
	void Render();

};