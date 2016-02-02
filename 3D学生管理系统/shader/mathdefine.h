


#pragma once

#include<math.h>
#include<d3d9.h>
#include<d3dx9.h>

#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")

#define UGP_FRONT    0
#define UGP_BACK     1
#define UGP_ON_PLANE 2
#define UGP_CLIPPED  3
#define UGP_CULLED   4
#define UGP_VISIBLE  5

const float eps =(float) 1e-8;
const float pi = (float)acos(-1.0);

int dcmp(float x);
float torad(float x);
