


#pragma once

#include"MathLib.h"

struct Ray3D {

	Ray3D() {} 
	Ray3D(point3D p0, vector3D dir): p0(p0), dir(dir) {


	}

	point3D p0;
	vector3D dir;
};



bool IntersectSphere(Ray3D &ray, point3D &o, float r);   // ���ߺ����ཻ
bool IntersectTriangle(Ray3D &ray, point3D &p1, point3D &p2, point3D &p3, point3D *ans); //�������ཻ  p1p2p3˳ʱ��

void fuck();