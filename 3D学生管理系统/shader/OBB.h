#pragma once

#include"d3dutil.h"

struct OBB {

	OBB();
	~OBB();
	void SetSize(D3DXVECTOR3 size);
	void Release() { RELEASE(m_mesh); }

	bool intersect(const OBB &obb);
	bool intersect(const D3DXVECTOR3 &point);

	virtual void render();
	void move(float x, float y, float z) {
		m_pos += D3DXVECTOR3(x,y,z);
	}

	D3DXVECTOR3 m_pos;
	D3DXQUATERNION m_dir;
	D3DXVECTOR3 m_size;
	ID3DXMesh *m_mesh;
	vector<D3DXVECTOR3> m_corner;


};
bool isCollision(OBB &obb1, OBB &obb2);
