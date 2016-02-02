#pragma once

#include"math/Line.h"

inline point2D ToP2D(D3DXVECTOR3 &p) 
{
	return point2D(p.x, p.z);
}

struct NavigationCell 
{
	enum { VTX_A, VTX_B, VTX_C };
	enum { SIDE_AB, SIDE_BC, SIDE_CA };
	
	// struct of cell
	point2D m_vertex[3];  // ABC
	line2D m_side[3];			// AB BC AC
	point2D m_midpoint;
	point2D m_midofwall[3];
	std::vector<NavigationCell*> m_adjcell;
	std::vector<float> m_edgecost;
	std::vector<int> m_adjwall;

	// for finding
	float g, h;
	int vis;
	bool open;
	int m_arrivewall;
	NavigationCell *precell;

	NavigationCell() {}
	void init(D3DXVECTOR3 &p1, D3DXVECTOR3 &p2, D3DXVECTOR3 &p3);
	void AddAdjface(NavigationCell* cell);

	// for finding
	float ComputeH(point2D p);
	void FindingInit();
};


inline void NavigationCell::init(D3DXVECTOR3 &p1, D3DXVECTOR3 &p2, D3DXVECTOR3 &p3)
{
	m_vertex[VTX_A] = ToP2D(p1);
	m_vertex[VTX_B] = ToP2D(p2);
	m_vertex[VTX_C] = ToP2D(p3);

	m_side[SIDE_AB] = line2D(m_vertex[VTX_A], m_vertex[VTX_B]);
	m_side[SIDE_BC] = line2D(m_vertex[VTX_B], m_vertex[VTX_C]);
	m_side[SIDE_CA] = line2D(m_vertex[VTX_C], m_vertex[VTX_A]);

	m_midpoint = (m_vertex[VTX_A] + m_vertex[VTX_B] + m_vertex[VTX_C])/3;

	for(int i=0;i<3;++i) 
		m_midofwall[i] = (m_side[i].a + m_side[i].b)/2;

	m_adjcell.clear();
	vis = -1;
}

inline void NavigationCell::AddAdjface(NavigationCell* cell) {
	// adjcell
	m_adjcell.push_back(cell);
	if(cell) {
		int i,j, ii=-1, jj=-1;
		// find adj wall
		for(i=0;i<3;++i) {
			for(j=0;j<3;++j) {
				if(m_midofwall[i] == cell->m_midofwall[j]) {
					ii=i;
					jj=j;
					break;
				}
			}
			if(ii+1) break;
		}
		assert(ii != -1);
		assert(jj != -1);
		float c = abs(m_midofwall[ii]-m_midpoint) + abs(cell->m_midpoint-cell->m_midofwall[jj]);
		m_adjwall.push_back(ii);
		m_edgecost.push_back(c);
	}
	else {
		m_adjwall.push_back(-1);
		m_edgecost.push_back(11111);
	}
}


inline void NavigationCell::FindingInit()
{
	vis = -1;
	open = 0;
	m_arrivewall = -1;
	precell = 0;
}


inline float NavigationCell::ComputeH(point2D p)
{
	point2D t = p-m_midpoint;
	return fabs(t.x) + fabs(t.y);
}
