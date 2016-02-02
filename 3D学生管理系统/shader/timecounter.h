
#pragma once

#include<windows.h>
#pragma comment(lib, "Winmm.lib")

struct TimeCounter {
  int sec;
	DWORD tpre, tnow;
	TimeCounter(int sec=0):sec(sec*1000) {
			tpre = tnow = timeGetTime();
	}
	bool intime() {
		if(!sec) return 1;
		tnow = timeGetTime();
		return tnow-tpre<sec;
	}
};
