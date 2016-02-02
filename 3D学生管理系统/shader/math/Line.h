#pragma once



#include"../d3dutil.h"
#include"vectors.h"



// ------------ line2D ----------
// 有向线段
// 向右是正方向`
struct line2D
{
	// 点和有向直线的关系
	enum { LEFT_SIDE=0, RIGHT_SIDE, ON_LINE }; 

	point2D a, b;
	line2D() {}
	line2D(point2D a, point2D b):a(a), b(b) {}

	int ClassifyPoint(point2D p);
};


// classfy p on the right or left or online
inline int line2D::ClassifyPoint(point2D p) 
{
	// AB旋转-90的法线， 
	vector2D n;
	vector2D v = b-a;
	n.x = v.y;
	n.y = -v.x;

	float d = dot(n, p-a);
	if(d > 0) return RIGHT_SIDE;
	else if(d < 0) return LEFT_SIDE;
	return ON_LINE;
}





