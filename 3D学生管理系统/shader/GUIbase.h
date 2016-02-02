
#pragma once


#include<vector>
#include<Windows.h>
#include<tchar.h>
#include<ctime>
#include<d3dx9.h>
#include<d3d9.h>



struct GUIVTX
{
	float x, y, z, rhw;
	DWORD color;
	float u, v;
	GUIVTX();
	GUIVTX(float x, float y, float z, float rhw, DWORD color, float u, float v) : x(x), y(y), z(z),
		rhw(rhw), color(color), u(u), v(v) {}
	static const int FVF = (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);
};

enum ControlType
{
	Cbutton = 1,
	Ctext,
	Cstext
};



// ----------------------------- ¿Ø¼þbase ---------------------------
class GUIcontrol
{
public:
	LPDIRECT3DDEVICE9 device;
	ID3DXFont *pFont;
	ControlType m_type;
	std::string m_name;

	bool m_focus;
	bool m_vis;
	int m_x, m_y;
	int m_windowWidth, m_windowHeight;

	GUIcontrol(LPDIRECT3DDEVICE9 device, int w, int h, std::string name="") :device(device), m_windowWidth(w),
		m_windowHeight(h), m_name(name)
	{
		m_focus = 0;
		m_vis = 1;
		/*D3DXCreateFont(device, h, h, 0, 1, FALSE, DEFAULT_CHARSET,
			OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, 0, "ËÎÌå", &pFont);*/

	}
	virtual ~GUIcontrol() {
		if (pFont) {
			pFont->Release();
			pFont = 0;
		}
	}

	void setX(int x) { m_x = x; }
	void setY(int y) { m_y = y; }
	void setWidth(int w) { m_windowWidth = w; }
	void setHeight(int h) { m_windowHeight = h; }
	int GetWidth() { return m_windowWidth; }
	int GetHeight() { return m_windowHeight; }
	void setVis(bool v) { m_vis = v; }



	virtual void OnRender() {}
	// msg
	virtual void ProcessMouse(int x, int y, int isdown) {}
	virtual void ProcessKey(WPARAM wparam, LPARAM lparam) {}
};

