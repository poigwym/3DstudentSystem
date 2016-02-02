#include "Quaternion.h"
#include <math.h>

#define CLAMP(x , min , max) ((x) > (max) ? (max) : ((x) < (min) ? (min) : x))


 Quaternion::Quaternion(D3DXVECTOR3 v, float sita) {
	 float tsin = sin(sita/2);
	w = cos(sita/2);
	x = v.x*tsin;
	y = v.y*tsin;
	z = v.z*tsin;
}


void Quaternion::SetEulerAngle(const EulerAngle &ea)
{
	float fCosHRoll = cos(ea.m_fRoll * .5f);
	float fSinHRoll = sin(ea.m_fRoll * .5f);
	float fCosHPitch = cos(ea.m_fPitch * .5f);
	float fSinHPitch = sin(ea.m_fPitch * .5f);
	float fCosHYaw = cos(ea.m_fYaw * .5f);
	float fSinHYaw = sin(ea.m_fYaw * .5f);

	w = fCosHRoll * fCosHPitch * fCosHYaw + fSinHRoll * fSinHPitch * fSinHYaw;
	x = fCosHRoll * fSinHPitch * fCosHYaw + fSinHRoll * fCosHPitch * fSinHYaw;
	y = fCosHRoll * fCosHPitch * fSinHYaw - fSinHRoll * fSinHPitch * fCosHYaw;
	z = fSinHRoll * fCosHPitch * fCosHYaw - fCosHRoll * fSinHPitch * fSinHYaw;
}

EulerAngle Quaternion::GetEulerAngle() const
{
	EulerAngle ea;

	ea.m_fRoll  = atan2(2 * (w * z + x * y) , 1 - 2 * (z * z + x * x));
	ea.m_fPitch = asin(CLAMP(2 * (w * x - y * z) , -1.0f , 1.0f));
	ea.m_fYaw   = atan2(2 * (w * y + z * x) , 1 - 2 * (x * x + y * y));

	return ea;
}

Quaternion Quaternion::operator*(const Quaternion &q) {
	Quaternion res;
	res.w = w*q.w - x*q.x - y*q.y - z*q.z;
	res.x = w*q.x + q.w*x + y*q.z - z*q.y;
	res.y = w*q.y + q.w*y + z*q.x - q.z*x;
	res.z = w*q.z + q.w*z + x*q.y - y*q.x;
	return res;
}

Quaternion Normal(Quaternion q) {
	float len = sqrt(q.w*q.w + q.x*q.x + q.y*q.y + q.z*q.z);
	q.w/=len;
	q.x/=len;
	q.y/=len;
	q.z/=len;
	return q;
}


D3DXVECTOR3 rotate(D3DXVECTOR3 v, Quaternion q) {
	Quaternion q_, qv;
	q = Normal(q);
	q_.w = q.w; q_.x = -q.x; q_.y = -q.y; q_.z = -q.z;
	qv.w = 0; qv.x=v.x; qv.y=v.y; qv.z=v.z;
	Quaternion aa= q_*qv*q;
	return D3DXVECTOR3(aa.x, aa.y, aa.z);
}