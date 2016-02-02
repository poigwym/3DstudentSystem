#pragma once



#include"d3dutil.h"


struct CrowdEntity 
{
	vector<CrowdEntity*> *q;
	typedef vector<CrowdEntity*>::iterator Cit;
	CrowdEntity();
	~CrowdEntity();
	void UpdateCrowd();
	virtual void Render() {}
	D3DXVECTOR3 KeepDis();
	D3DXVECTOR3 SetMagnitudeOfVector(D3DXVECTOR3 &v, float m);
	D3DXVECTOR3 GetRandomLocation() {
		return D3DXVECTOR3(((rand() % 1000) / 1000.0f) * 20.0f - 10.0f,
			0.0f,
			((rand() % 1000) / 1000.0f) * 20.0f - 10.0f);
	}

	D3DXVECTOR3 m_pos, m_vel, m_tar;
};



// ----------------------- Crow control -----------------

struct Crowd 
{
	vector<CrowdEntity*> q;
	Crowd();
	~Crowd();

	void InsCrowEntity(CrowdEntity *p);
	void UpdateCrowd();
	void Render() {
		for(int i=0;i<q.size();++i) 
			q[i]->Render();
	}
};