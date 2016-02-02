
#include"IKanimation.h"

//extern ofstream fout;
 // ---------------------------  Head IK -----------------------------------

HeadIK::HeadIK(LPCSTR filename):SkinMesh(filename) {
	
	m_headbone = (Bone*) D3DXFrameFind(m_boneroot, "Head");
	if(!m_headbone) {
		MCOUT("find head fail");
		exit(1);
	}
	D3DXMATRIX m_localHead;
	D3DXMatrixInverse(&m_localHead, 0, &m_headbone->combmat);
	// local org foreward vector
	D3DXVec3TransformNormal(&m_HeadForeward, &D3DXVECTOR3(0, 0, -1), &m_localHead);
	D3DXVec3Normalize(&m_HeadForeward, &m_HeadForeward);
}



// 每次调用要调整整个骨架的comb
void HeadIK::LookAt(D3DXVECTOR3 lookat) {
	D3DXVECTOR3 pos,  axis;
	D3DXMATRIX m_localHead;
	// new sight
	D3DXMatrixInverse(&m_localHead, 0, &m_headbone->combmat);
	D3DXVec3TransformCoord(&pos, &lookat, &m_localHead);
	// Axis = org sight X new sight
	D3DXVec3Cross(&axis, &m_HeadForeward, &pos);
	D3DXVec3Normalize(&axis, &axis);
	D3DXVec3Normalize(&pos, &pos);  
	float ang = acos(D3DXVec3Dot(&pos, &m_HeadForeward));
	ang = min(ang, 60*D3DX_PI/180);
	D3DXMATRIX rot;
	D3DXMatrixRotationAxis(&rot, &axis, ang);
	m_headbone->combmat = rot * m_headbone->combmat;
	UpdateMatrix((Bone*)m_headbone->pFrameFirstChild, &m_headbone->combmat);
}



void HeadIK::updateHeadIK() {
	POINT p;
	GetCursorPos(&p);
	float x = max(0, min(p.x, 800));
	float y = max(0, min(p.y, 600));
	x = (x-400)/800;
	y = (y-300)/600;
  
	D3DXVECTOR3 v = D3DXVECTOR3(x, 1.5-y, -1);
	LookAt(v);
}



// ------------------------ Arm IK --------------------------------

void GetMatPos(D3DXMATRIX *mat, D3DXVECTOR3 *pos) {
	pos->x = mat->_41; pos->y = mat->_42; pos->z = mat->_43;
}

ArmIK :: ArmIK(char *filename):SkinMesh(filename) 
{
	m_shoulder = (Bone*)D3DXFrameFind(m_boneroot, "Bone20");
	m_elbow = (Bone*)D3DXFrameFind(m_boneroot, "Bone21");
	m_hand = (Bone*)D3DXFrameFind(m_boneroot, "Bone27");

	

}


// O的世界矩阵，2个世界点， 返回在O坐标系p1到p2的旋转矩阵
void GetRotation(D3DXMATRIX mat, D3DXVECTOR3 p1, D3DXVECTOR3 p2, D3DXMATRIX *res) 
{
	D3DXMatrixInverse(&mat, 0, &mat);
	D3DXVec3TransformCoord(&p1, &p1, &mat);
	D3DXVec3TransformCoord(&p2, &p2, &mat);
	D3DXVec3Normalize(&p1, &p1);
	D3DXVec3Normalize(&p2, &p2);
	float ang;
	ang =  acos(D3DXVec3Dot(&p1, &p2));
	D3DXVECTOR3 axis;
	D3DXVec3Cross(&axis, &p1, &p2);
	D3DXMatrixRotationAxis(res, &axis, ang);
}


void GetAxis(D3DXMATRIX mat, D3DXVECTOR3 p1, D3DXVECTOR3 p2, D3DXVECTOR3 *axis) 
{
	D3DXMatrixInverse(&mat, 0, &mat);
	D3DXVec3TransformCoord(&p1, &p1, &mat);
	D3DXVec3TransformCoord(&p2, &p2, &mat);
	D3DXVec3Normalize(&p1, &p1);
	D3DXVec3Normalize(&p2, &p2);
	float ang;
	ang =  acos(D3DXVec3Dot(&p1, &p2));
	D3DXVec3Cross(axis, &p1, &p2);
}
 
void ArmIK ::grab(D3DXVECTOR3 tar) 
{
	D3DXVECTOR3 beg, joint, end;
	GetMatPos(&m_shoulder->combmat, &beg);
	GetMatPos(&m_elbow->combmat, &joint);
	GetMatPos(&m_hand->combmat, &end);
	D3DXVECTOR3 begtojoint, jointtoend;
	begtojoint = joint-beg;
	jointtoend = end-joint;
	int c=1;
	while(D3DXVec3Length(&(end-tar)) > 0.01 && c--) 
	{
		D3DXMATRIX ElbowRotation, WorldElbowRotation;
		GetRotation(m_elbow->combmat, end, tar, &ElbowRotation);
	D3DXVECTOR3	jointtoend = end-joint;
	D3DXVECTOR3	jointtotar = tar-joint;
		D3DXVec3Normalize(&jointtoend, &jointtoend);
		D3DXVec3Normalize(&jointtotar, &jointtotar);
		float ang;
		float a=D3DXVec3Length(&(tar-joint)), 
					b=D3DXVec3Length(&(beg-joint)), 
					c=D3DXVec3Length(&(tar-beg)); 
		float ang1 ;
		if(a+b <= c) ang1 = D3DX_PI;
		else ang1=acos((a*a+b*b-c*c)/(2*a*b));
		float ang2 = acos(D3DXVec3Dot(&(-begtojoint), &jointtoend));
		ang = ang1-ang2;
		D3DXVECTOR3 axis;     // elbow空间的旋转轴
		GetAxis(m_elbow->combmat, end, tar, &axis);   
		D3DXMatrixRotationAxis(&ElbowRotation, &axis, ang);
		D3DXVec3TransformNormal(&axis, &axis, &m_elbow->combmat);  // 绕elbow的世界转轴
		D3DXMatrixRotationAxis(&WorldElbowRotation, &axis, ang);
		D3DXVec3TransformCoord(&end, &end, &WorldElbowRotation);
		m_elbow->TransformationMatrix = ElbowRotation * m_elbow->TransformationMatrix;
		if(D3DXVec3Length(&(end-tar)) < 0.01) break;
		D3DXMATRIX ShoulderRotation;
		GetRotation(m_shoulder->combmat, end, tar, &ShoulderRotation);
		m_shoulder->combmat = ShoulderRotation * m_shoulder->combmat;
	}
	UpdateMatrix((Bone*)m_shoulder->pFrameFirstChild, &m_shoulder->combmat);
}



void ArmIK::updateArmIK() {
	POINT p;
	GetCursorPos(&p);
	float x = max(0, min(p.x, 800));
	float y = max(0, min(p.y, 600));
	x = (x-400)/800;
	y = (y-300)/600;
  
	D3DXVECTOR3 v = D3DXVECTOR3(x, 1.5-y, -1);
	grab(v);
}

