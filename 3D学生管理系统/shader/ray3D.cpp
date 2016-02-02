

#include"ray3D.h"

bool IntersectSphere(Ray3D &ray, point3D &o, float r) {
	vector3D v = o-ray.p0;
	float d = abs(v);
	float d2 = dot(v, ray.dir); // 切线长的平方

	if(dcmp(d2) < 0) return 0;

	float  d3 = d2 + r*r - d*d;

	if(dcmp(d3) < 0) return 0;
	return 1;
}

bool IntersectTriangle(Ray3D &ray, point3D &p1, point3D &p2, point3D &p3, point3D *ans) {

	vector3D E1 = p2-p1, E2 = p3-p1;
	vector3D T = ray.p0 - p1;

	vector3D P = xmul(ray.dir, E2);
	float det = fabs(dot(P, E1));

	if(dcmp(det)<0) {
		T = p1-ray.p0;
		det = -det;
	}

	if(dcmp(det)==0)
		return 0;

	vector3D Q = xmul(T, E1);
	float t, u, v;
	u = dot(P, T);
	if(dcmp(u)<0 || dcmp(u-det)>0) 
		return 0;
	v = dot(Q, ray.dir);
	if(dcmp(v)<0 || dcmp(u+v-det)>0)
		return 0;
	t = dot(Q, E2);

	if(ans) {
		*ans = p1*(1-u-v) + p2*u + p3*v;
		*ans /= det;
	}

	return 1;
}

