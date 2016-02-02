

#pragma once 
#include<cstring>
#include<d3dx9.h>
#include<vector> 
#include"timecounter.h"
using namespace std;

#pragma  comment(lib, "D3dx9.lib")


//temporary output
struct tmpstr{
	char *s;
	int x, y;
	TimeCounter tc;

	tmpstr() { s=0; }
	tmpstr(const tmpstr &t) {
		*this = t;
	}
	void operator = (const tmpstr &t) {
		x=t.x, y=t.y;
		if(!t.s) return;
		s=new char[strlen(t.s)+1];
		strcpy(s, t.s);
		tc=t.tc;
	}
	~tmpstr() {
		if(s) delete []s;
		s=0;
	}
};

struct TYPER {
	int rnum, cnum, WIDTH, HEIGHT, width, height;
	ID3DXFont *pFont;	
	LPDIRECT3DDEVICE9 m_device;
	vector<tmpstr> q;

	inline void ins(char *s, int x, int y, int sec) {
		q.push_back(tmpstr());
		tmpstr &ts = q[(int)q.size()-1];
		ts.x = x, ts.y =y;
		ts.s = new char[strlen(s)+1];
		strcpy(ts.s, s);
		ts.tc = TimeCounter(sec);
	}

	TYPER(LPDIRECT3DDEVICE9 pDevice, int _WIDTH, int _HEIGHT, int _width, int _height):m_device(pDevice) {
		WIDTH = _WIDTH;
		HEIGHT = _HEIGHT;
		width = _width;
		height = _height;
		rnum = HEIGHT / height;
		cnum = WIDTH / width;
		
		D3DXCreateFont(m_device, width, height, 0, 1, FALSE, DEFAULT_CHARSET, 
			OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, 0, TEXT("ËÎÌו"), &pFont);
	}

	void render(const char *str, int x, int y) {
		int len=strlen(str);
		RECT rc;
		rc.left = x; rc.top = y;
		rc.right = (x+len*width>WIDTH? WIDTH:x+len*width);
		rc.bottom = y+(2+(len-(WIDTH-x)/width)/cnum)*height;
		pFont->DrawText(0, str, len, &rc, DT_LEFT, D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256));
	}

	void renderall() {
		for(vector<tmpstr>::iterator  i=q.begin(); i!=q.end(); ) {
			if(!i->tc.intime()) i=q.erase(i);
			else ++i;
		}

		for(unsigned i=0;i<q.size();++i)  
			render(q[i].s, q[i].x, q[i].y);
	}
};