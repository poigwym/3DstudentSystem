#pragma once

#include "EulerAngle.h"
#include"d3dutil.h"
class Quaternion
{
public:
	float x , y , z , w;
public:
	Quaternion(const Quaternion &q) { w=q.w, x=q.x; y=q.y;z=q.z; }
	Quaternion(void) : x(0.0f) , y(0.0f) , z(0.0f) , w(1.0f) {}
	Quaternion(D3DXVECTOR3 v, float sita);
	~Quaternion(void) {}
	void SetEulerAngle(const EulerAngle& ea);
	EulerAngle GetEulerAngle() const;
	Quaternion operator*(const Quaternion &q);
};
Quaternion Normal(Quaternion q);
D3DXVECTOR3 rotate(D3DXVECTOR3 v, Quaternion q);
