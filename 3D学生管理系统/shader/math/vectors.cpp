
#include"vectors.h"


// --------------------- vector2D ------------------


//2D
float dot(vector2D &v1, vector2D &v2) {
	return v1.x*v2.x + v1.y*v2.y;
}

float xmul(vector2D &v1, vector2D &v2) {
	return v1.x*v2.y - v1.y*v2.x;
}

float abs(vector2D &v) {
	return sqrt(v.x*v.x + v.y*v.y);
}

void Normal(vector2D &v) {
	float len = 1.0f / abs(v);
	v.x *= len;
	v.y *= len;
}

float betweenangle(vector2D &v1, vector2D&v2) {
	float f = abs(v1)*abs(v2);
	if (!dcmp(f)) f = eps;
	return acos(dot(v1, v2) / f);
}





// ------------------- vector3D --------------



vector3D::vector3D(float x, float y, float z):x(x),y(y),z(z) {
}

vector3D vector3D::operator =(vector3D &v) {
	x = v.x; y = v.y; z = v.z;
	return *this;
}

vector3D vector3D::operator -(vector3D &v) {
	return vector3D(x - v.x, y - v.y, z - v.z);
}

vector3D vector3D::operator +(vector3D &v) {
	return vector3D(x + v.x, y + v.y, z + v.z);
}

vector3D vector3D::operator *(vector3D &v) {
	return vector3D(x * v.x, y * v.y, z * v.z);
}


vector3D vector3D::operator /(vector3D &v) {
	return vector3D(x / v.x, y / v.y, z / v.z);
}

vector3D vector3D::operator +(float f) {
	return vector3D(x + f, y + f, z + f);
}

vector3D vector3D::operator -(float f) {
	return vector3D(x - f, y - f, z - f);
}

vector3D vector3D::operator *(float f) {
	return vector3D(x * f, y * f, z * f);
}

vector3D vector3D::operator /(float f) {
	f = 1/f;
	return vector3D(x * f, y * f, z * f);
}

void vector3D::operator +=(vector3D &v) {
	x += v.x; y += v.y; z += v.z;
}

void vector3D::operator -=(vector3D &v) {
	x -= v.x; y -= v.y; z -= v.z;
}

void vector3D::operator *=(vector3D &v) {
	x *= v.x; y *= v.y; z *= v.z;
}

void vector3D::operator /=(vector3D &v) {
	x /= v.x; y /= v.y; z /= v.z; 
} 

void vector3D::operator +=(float f) {
	x += f; y += f; z += f;
}

void vector3D::operator -=(float f) {
	x -= f; y -= f; z -= f;
}

void vector3D::operator *=(float f) {
	x *= f; y *= f; z *= f;
}

void vector3D::operator /=(float f) {
	f = 1/f; x *= f; y *= f; z *= f;
}

vector3D xmul(vector3D &v1, vector3D &v2) {
	return vector3D(v1.y*v2.z - v1.z*v2.y,
								  v1.z*v2.x - v1.x*v2.z,
									v1.x*v2.y - v1.y*v2.x);
}

float dot(vector3D &v1, vector3D &v2) {
	return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
}

float abs(vector3D &v) {
	return sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
}

void normal(vector3D &v) {
	float len = abs(v);
	v.x/=len; v.y/=len; v.z/=len;
}

vector3D MakeNormal(point3D &p1, point3D &p2, point3D &p3) {
	vector3D ans = xmul(p2-p1, p3-p1);
	normal(ans);
	return ans;
}

