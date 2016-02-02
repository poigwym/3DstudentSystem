


#pragma once

#include"MathLib.h"
#include"vectors.h"

class matrix4x4 {
public:
	matrix4x4() { Identity(); }
	matrix4x4(const matrix4x4 &m);
	matrix4x4(float r11, float r12, float r13, float r14,
		float r21, float r22, float r23, float r24,
		float r31, float r32, float r33, float r34,
		float r41, float r42, float r43, float r44);
	~matrix4x4() {}


	void operator=(matrix4x4 &m);
	matrix4x4 operator-(matrix4x4 &m);
	matrix4x4 operator+(matrix4x4 &m);
	matrix4x4 operator*(matrix4x4 &m);

	matrix4x4 operator*(float f);
	matrix4x4 operator/(float f);

	void operator +=(matrix4x4 &m);
	void operator -=(matrix4x4 &m);
	void operator *=(matrix4x4 &m);

	void operator *=(float f);
	void operator /=(float f);

	void Identity();
	void Translate(vector3D &Translate);
	void Translate(float x, float y, float z);
	void inverseTranslate();

	void Rotate(double angle, int x, int y, int z);

	vector3D VectorMatrixMultiply(vector3D &v);
	vector3D VectorMatrixMultiply3x3(vector3D &v);

	float matrix[16];
};