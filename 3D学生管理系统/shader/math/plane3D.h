
#pragma once

#include"MathLib.h"

struct plane3D {

	plane3D(float a=0, float b=0, float c=0, float d=0);
	void setnormal(float a, float b, float c, float d);
	
	float a, b, c, d;
};

plane3D CreatePlane3Point(point3D &p1, point3D &p2, point3D &p3);   // 三点确定平面 p1p2 -> p1p3 逆时 
int ClassifyPointPos(plane3D &p, vector3D &v);											//点在平面的哪侧
int ClassifyPointPos(plane3D &p, float x, float y, float z);
float PointToPlane3D(plane3D &pl, point3D &p);
float PointToPlane3D(plane3D &p, float x, float y, float z);  
bool Intersect(plane3D &s1, plane3D &s2, point3D *intersectPoint);   //平面相交直线的一点

