#pragma once


#include"d3dutil.h"
#include"drawgraph.h"

struct BHV
{
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_box;


	BHV(){}
	BHV(D3DXVECTOR3 pos, D3DXVECTOR3 box):m_pos(pos), m_box(box) {}
	BHV(const BHV &bhv):m_pos(bhv.m_pos) , m_box(bhv.m_box) {}

	virtual void render() {}
};



struct OCT 
{

	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_box;
	int m_lv, m_maxn;
	int m_objnum;
	OCT *m_ch[8];
	std::vector<BHV*> m_objs;
	std::vector<D3DXVECTOR3> m_corner;

	// for divide
	static int dx[8] ;
	static int dy[8] ;
	static int dz[8] ;


	OCT() { 
		memset(m_ch,0, sizeof(m_ch));
		m_lv = m_maxn = m_objnum = 0;
		m_box = m_pos = D3DXVECTOR3(0,0,0);
	}
	OCT(D3DXVECTOR3 pos,	D3DXVECTOR3 box, int lv, int maxn):m_pos(pos), m_box(box),
		m_lv(lv), m_maxn(maxn){
		memset(m_ch,0,sizeof(m_ch));
		m_objnum = 0;

		for(int i=0;i<8;++i) 
			m_corner.push_back(
				D3DXVECTOR3(m_pos.x+dx[i]*m_box.x, m_pos.y+dy[i]*m_box.y, m_pos.z+dz[i]*m_box.z));
		m_objs.clear();
	}

	void Ins(BHV *v);
	bool ispushdown(const D3DXVECTOR3 &subpos, const D3DXVECTOR3 &subbox, BHV *v);
	void outputframework();
	void outputobj();

	// output the debug framework
	void debugbuild();
	void debugoutput();
};




