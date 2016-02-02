#pragma once


#include<cmath>
#include<iostream>
#include<cstdio>
#include<iomanip>


inline int RandAB(int mn, int mx) 
{
	return rand() % (mx - mn) + mn;
}
