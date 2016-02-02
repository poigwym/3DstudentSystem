#pragma once


#include"navigcell.h"
#include"Mesh.h"



struct NavigationNode 
{
	NavigationCell *cell;
	float m_cost;
	NavigationNode(NavigationCell *cell=0):cell(cell) {
		if(cell) 
			m_cost = cell->g + cell->h;
	}
	bool operator < (const NavigationNode &t) const {
		return m_cost > t.m_cost;
	}
};




struct NavigationMesh 
{

	// map
	std::vector<NavigationCell*> m_cells;

	// for finding
	std::vector<point2D> m_path;
	int m_vis;
	NavigationCell *begcell, *tarcell;

	// init
	NavigationMesh(Mesh *mesh);
	void BuildMap(Mesh *mesh);
	
	// functional
	bool FindPath(D3DXVECTOR3 beg, D3DXVECTOR3 tar);
	// --- helper
	NavigationCell* Findclosestcell(point2D p);
	
	void MakePath(NavigationCell *begcell, NavigationCell *tarcell);
	//bool SightTestOfTwoPoint(NavigationCell &cella, NavigationCell &cellb);
};


// navigation path
// for output path

struct NavigationPath
{
	enum { stand = 0, walk = 1 };
	point2D m_pos;
	vector2D m_dir;

	// for walking
	vector<point2D> m_path;
	int m_curstep;
	int m_state;
	NavigationPath(point2D pos) :m_pos(pos)
	{
		m_state = stand;
	}
	void update() {
		if (m_state == walk)
		{
			m_pos = m_pos + (m_path[m_curstep] - m_pos)*0.5;
			m_dir = m_path[m_curstep] - m_pos;
			if (abs(m_pos-m_path[m_curstep]) < 0.1)
			{
				++m_curstep;
				if (m_curstep == m_path.size())
					m_state = stand;
			}
		}
	}

	void setpath(vector<point2D> pp)
	{
		m_path = pp;
		m_curstep = 0;
		m_state = walk;
	}

	void setpos(point2D pp) 
	{
		m_pos = pp;
	}

	float GetRotateAng() { 
		return atan2(m_dir.y, - m_dir.x) + D3DX_PI*0.5;
	}
};
