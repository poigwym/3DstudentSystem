


#include"OBB.h"

extern LPDIRECT3DDEVICE9 gdevice;


OBB::OBB() {
	m_mesh = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXQuaternionIdentity(&m_dir);
	SetSize(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
}


OBB::~OBB() {
	Release();
}


void OBB::SetSize(D3DXVECTOR3 size)
{
	Release();
	m_corner.clear();
	m_size = size;
	D3DXCreateBox(gdevice, m_size.x * 2.0f, m_size.y * 2.0f, m_size.z * 2.0f, &m_mesh, NULL);

	m_corner.push_back(D3DXVECTOR3(m_size.x, m_size.y, m_size.z));
	m_corner.push_back(D3DXVECTOR3(m_size.x, m_size.y, -m_size.z));
	m_corner.push_back(D3DXVECTOR3(m_size.x, -m_size.y, m_size.z));
	m_corner.push_back(D3DXVECTOR3(m_size.x, -m_size.y, -m_size.z));
	m_corner.push_back(D3DXVECTOR3(-m_size.x, m_size.y, m_size.z));
	m_corner.push_back(D3DXVECTOR3(-m_size.x, m_size.y, -m_size.z));
	m_corner.push_back(D3DXVECTOR3(-m_size.x, -m_size.y, m_size.z));
	m_corner.push_back(D3DXVECTOR3(-m_size.x, -m_size.y, -m_size.z));
	//m_radius = D3DXVec3Length(&m_size);
}


bool OBB::intersect(const OBB &obb) {
	D3DXMATRIX r1, r2, m;
	D3DXMatrixRotationQuaternion(&r2, &obb.m_dir);
	D3DXMatrixRotationQuaternion(&r1, &m_dir);
	D3DXMatrixInverse(&r1, 0, &r1);
	m = r2*r1;  // r2*r1^-1

	D3DXVECTOR3 XAxis(m._11, m._21, m._31);
	D3DXVECTOR3 YAxis(m._12, m._22, m._32);
	D3DXVECTOR3 ZAxis(m._13, m._23, m._33);
	D3DXVECTOR4 offset;
	D3DXVec3Transform(&offset, &(obb.m_pos - m_pos), &r1);
	// proj on Xaxis
	float sx=INF, ex=-INF;
	for(int i=0;i<8;++i)
		sx = min(sx, offset.x + obb.m_corner[i].x*XAxis.x + obb.m_corner[i].y*XAxis.y + obb.m_corner[i].z*XAxis.z);
	for(int i=0;i<8;++i) 
		ex = max(ex, offset.x + obb.m_corner[i].x*XAxis.x + obb.m_corner[i].y*XAxis.y + obb.m_corner[i].z*XAxis.z);
	
	if(sx > m_size.x || ex < -m_size.x) return 0;


	// proj on Yaxis
	float sy = INF, ey = -INF;
	for (int i = 0;i<8;++i)
		sy = min(sy, offset.y + obb.m_corner[i].x*YAxis.x + obb.m_corner[i].y*YAxis.y + obb.m_corner[i].z*YAxis.z);
	for (int i = 0;i<8;++i)
		ey = max(ey, offset.y + obb.m_corner[i].x*YAxis.x + obb.m_corner[i].y*YAxis.y + obb.m_corner[i].z*YAxis.z);
		

	if(sy > m_size.y || ey < -m_size.y) return 0;


	// proj on Zaxis
	float sz = INF, ez = -INF;
	for (int i = 0;i<8;++i)
		sz = min(sz,offset.z + obb.m_corner[i].x*ZAxis.x + obb.m_corner[i].y*ZAxis.y + obb.m_corner[i].z * ZAxis.z);
	for (int i = 0;i<8;++i)
		ez = max(ez,offset.z + obb.m_corner[i].x*ZAxis.x + obb.m_corner[i].y*ZAxis.y + obb.m_corner[i].z * ZAxis.z);

	if (sz > m_size.z || ez < -m_size.z) return 0;


	return 1;
}


bool isCollision(OBB &obb1, OBB &obb2) {
	return obb1.intersect(obb2) && obb2.intersect(obb1);
}




bool OBB::intersect(const D3DXVECTOR3 &point) {
	D3DXMATRIX world, rot, invworld;
	D3DXMatrixTranslation(&world, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixRotationQuaternion(&rot, &m_dir);
	world = rot*world;
	D3DXMatrixInverse(&invworld, 0, &world);
	D3DXVECTOR4 pt;
	D3DXVec3Transform(&pt, &point, &invworld);
	return  pt.x < fabs(m_size.x) || pt.y < fabs(m_size.y) || pt.z < fabs(m_size.z); 
}



void OBB::render() {
	D3DXMATRIX world, rot;
	//D3DXQuaternionNormalize(&m_dir, &m_dir);
	D3DXMatrixTranslation(&world,m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixRotationQuaternion(&rot, &m_dir);
	world = rot*world;
	gdevice->SetTransform(D3DTS_WORLD, &world);
	m_mesh->DrawSubset(0);
}