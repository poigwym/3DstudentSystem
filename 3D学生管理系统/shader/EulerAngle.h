#pragma once

class EulerAngle
{
public:
	float m_fYaw , m_fPitch, m_fRoll;
public:
	EulerAngle(void): m_fYaw(0.0f) , m_fPitch(0.0f) , m_fRoll(0.0f) {}
	~EulerAngle(void) {}
};
