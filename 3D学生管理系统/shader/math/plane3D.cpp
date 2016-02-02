
#include"plane3D.h"

plane3D::plane3D(float a, float b, float c, float d):a(a), b(b), c(c), d(d) {
}

void plane3D::setnormal(float _a, float _b, float _c, float _d){
	a=_a; b=_b; c=_c; d=_d;
}

plane3D CreatePlane3Point(point3D &p1, point3D &p2, point3D &p3) {
	vector3D n=MakeNormal(p1, p2, p3);
	return plane3D(n.x, n.y, n.z, -(n.x*p1.x + n.y*p1.y + n.z*p1.z));
}

int ClassifyPointPos(plane3D &p, vector3D &v) {
	int d = dcmp(p.a*v.x + p.b*v.y + p.c*v.z + p.d);
	if(d == 0) return UGP_ON_PLANE;
	else if(d > 0) return UGP_FRONT;
	else return UGP_BACK;
}

int ClassifyPointPos(plane3D &p, float x, float y, float z) {
	int d = dcmp(p.a*x + p.b*y + p.c*z + p.d);
	if(d == 0) return UGP_ON_PLANE;
	else if(d > 0) return UGP_FRONT;
	else return UGP_BACK;	
}

float PointToPlane3D(plane3D &pl, point3D &p)
{
	//return abs(a*p.x + b*p.y + c*p.z + d) / sqrt(a*a+b*b+c*c);  //单位法向量分母=1
	return fabs(pl.a*p.x + pl.b*p.y + pl.c*p.z + pl.d);
}

float PointToPlane3D(plane3D &p, float x, float y, float z) {
	return fabs(p.a*x + p.b*y + p.c*z + p.d);
}


bool Intersect(plane3D &s1, plane3D &s2, point3D *intersectPoint) {

	vector3D cross;
	vector3D n1(s1.a, s1.b, s1.c);
	vector3D n2(s2.a, s2.b, s2.c);
	float length = 0;

	cross = xmul(n1, n2);
	length = abs(cross);

	if(length < 1e-08f) return false;

	if(intersectPoint)
	{
		float l0 = dot(n1, n1);
		float l1 = dot(n1, n2);
		float l2 = dot(n2, n2);
		float det = l0 * l2 - l1 * l1;
		float invDet = 0;

		if(dcmp(length)==0) return 0;

		invDet = 1 / det;
		float d0 = (l2 * s1.d - l1 * s2.d) * invDet;
		float d1 = (l0 * s2.d - l1 * s1.d) * invDet;

		(*intersectPoint) = n1* d0 + n2* d1;
	}

	return 1;
}