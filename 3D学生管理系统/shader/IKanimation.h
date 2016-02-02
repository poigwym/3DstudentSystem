#pragma once


#include"animation.h"


struct HeadIK : public SkinMesh
{
	HeadIK(LPCSTR filename);
	void LookAt(D3DXVECTOR3 lookat);
	void updateHeadIK();

	D3DXVECTOR3 m_HeadForeward;
	Bone *m_headbone;
};


struct ArmIK : public  SkinMesh {
	ArmIK(char *filename);
	void grab(D3DXVECTOR3 pos);
	void updateArmIK();
	Bone *m_shoulder, *m_elbow, *m_hand;
};