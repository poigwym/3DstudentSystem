
#pragma once 

#include"mathdefine.h"

typedef struct vector2D {
	float x, y;
	vector2D(float x = 0, float y = 0) :x(x), y(y) {}
	vector2D(const vector2D &v):x(v.x), y(v.y) {}


	vector2D operator -(vector2D &v) {
		return vector2D(x - v.x, y - v.y);
	}
	vector2D operator +(vector2D &v) {
		return vector2D(x + v.x, y + v.y);
	}
	vector2D operator*(float f) {
		return vector2D(x*f, y*f);
	}
	vector2D operator/(float f) {
		return vector2D(x/f, y/f);
	}

	bool operator == (const vector2D &p) {
		return dcmp(x-p.x)==0 && dcmp(y-p.y)==0;
	}
} point2D;
float dot(vector2D &v1, vector2D &v2);
float xmul(vector2D &v1, vector2D &v2);
float abs(vector2D &v);
void Normal(vector2D &v);
float betweenangle(vector2D &v1, vector2D&v2);



typedef struct vector3D {
	vector3D() { x=y=z=0;}
	vector3D(float x, float y, float z);

	vector3D operator=(vector3D &v);
	vector3D operator-(vector3D &v);
	vector3D operator+(vector3D &v);
	vector3D operator*(vector3D &v);
	vector3D operator/(vector3D &v);

	vector3D operator+(float f);
	vector3D operator-(float f);
	vector3D operator*(float f);
	vector3D operator/(float f);

	void operator +=(vector3D &v);
	void operator -=(vector3D &v);
	void operator *=(vector3D &v);
	void operator /=(vector3D &v);
	void operator +=(float f);
	void operator -=(float f);
	void operator *=(float f);
	void operator /=(float f);

	float x, y, z;
} point3D;

vector3D xmul(vector3D &v1, vector3D &v2);
float dot(vector3D &v1, vector3D &v2);
float abs(vector3D &v);
void normal(vector3D &v);
vector3D MakeNormal(point3D &p1, point3D &p2, point3D &p3);



