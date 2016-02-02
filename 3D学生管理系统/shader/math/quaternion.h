
#pragma once

#include"MathLib.h"

struct quaternion {
	quaternion() {
		w=1;
		x=y=z=0;
	}
	quaternion(float x, float y, float z, float w):x(x), y(y), z(z), w(w){}

	quaternion operator +(const quaternion &t);
	quaternion operator *(const quaternion &t);



	float x, y, z, w;
};


float abs(quaternion &q);
void normal(quaternion &q);
quaternion conjugate(quaternion &q);

quaternion RotateAxis(vector3D &v, float sita) ;
quaternion RotationRadiansf(double X, double Y, double Z);
void QuatToMat(quaternion &q, float *mat);