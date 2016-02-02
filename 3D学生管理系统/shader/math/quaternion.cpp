
#include "quaternion.h"
quaternion quaternion::operator +(const quaternion &q) {
	return quaternion(x+q.x, y+q.y, z+q.z, w+q.w);
}

quaternion quaternion::operator *(const quaternion &q) {
	return quaternion(w * q.x + x * q.w + y * q.z - z * q.y,
		w * q.y - x * q.z + y * q.w + z * q.x,
		w * q.z + x * q.y - y * q.x + z * q.w,
		w * q.w - x * q.x - y * q.y - z * q.z);
}

float abs(quaternion &q) {
	return sqrt(q.x*q.x + q.y*q.y + q.z*q.z + q.w*q.w);
}

void normal(quaternion &q) {
	float len = 1.0f/abs(q);
	q.x*=len;
	q.y*=len;
	q.z*=len;
}

quaternion conjugate(quaternion &q) {
	return quaternion(-q.x, -q.y, -q.z, q.w);
}

quaternion RotateAxis(vector3D &v, float sita) {
	quaternion ans;
	normal(v);

	float sin0 = sin(sita/2);
	float cos0 = cos(sita/2);

	ans.w = cos0;
	ans.x = sin0*v.x;
	ans.y = sin0*v.y;
	ans.z = sin0*v.z;
	return ans;
}

quaternion RotationRadiansf(double X, double Y, double Z) {
	quaternion ans;
	double cosX, cosY, cosZ;
	double sinX, sinY, sinZ;
	double cosXY, sinXY;

	sinX = sin(X * 0.5);
	cosX = cos(X * 0.5);

	sinY = sin(Y * 0.5);
	cosY = cos(Y * 0.5);

	sinZ = sin(Z * 0.5);
	cosZ = cos(Z * 0.5);

	cosXY = cosX * cosY;
	sinXY = sinX * sinY;

	ans.x = (float)(sinX * cosY * cosZ - cosX * sinY * sinZ);
	ans.y = (float)(cosX * sinY * cosZ + sinX * cosY * sinZ);
	ans.z = (float)(cosXY * sinZ - sinXY * cosZ);
	ans.w = (float)(cosXY * cosZ + sinXY * sinZ); 
	return ans;
}


void QuatToMat(quaternion &q, float *mat) {
	if(!mat) return;

	float x=q.x, y=q.y, z=q.z, w=q.w;
	mat[0]  = 1.0f - 2.0f * (y * y + z * z); 
	mat[1]  = 2.0f * (x * y + z * w);
	mat[2]  = 2.0f * (x * z - y * w);
	mat[3]  = 0.0f;  

	mat[4]  = 2.0f * (x * y - z * w);  
	mat[5]  = 1.0f - 2.0f * (x * x + z * z); 
	mat[6]  = 2.0f * (z * y + x * w);  
	mat[7]  = 0.0f;  

	mat[8]  = 2.0f * (x * z + y * w);
	mat[9]  = 2.0f * (y * z - x * w);
	mat[10] = 1.0f - 2.0f * (x * x + y * y);  
	mat[11] = 0.0f;  

	mat[12] = 0;  
	mat[13] = 0;  
	mat[14] = 0;  
	mat[15] = 1.0f;
}
