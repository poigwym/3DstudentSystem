
#include"mathdefine.h"




int dcmp(float x) { 
	if(fabs(x) < eps) return 0;
	return x < 0? -1:1;
}

//¼«½Ç
float torad(float x) { return x*pi/180.0f; }