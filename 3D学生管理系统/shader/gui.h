
#pragma once


#include<vector>
#include<Windows.h>
#include<tchar.h>
#include<ctime>
#include<d3dx9.h>
#include<d3d9.h>

#include"GUIbase.h"
#include"GUIbutton.h"
#include"GUITextBox.h"
#include"GUIstaticText.h"



// --------------------------- GUI π‹¿Ì∆˜ --------------------------
struct GUIwindow
{
	LPDIRECT3DDEVICE9 device;
	ID3DXFont *pFont;
	int mouseX, mouseY;
	std::string m_name;

	std::vector<GUIcontrol*> m_controls;
	int m_x, m_y;
	int m_windowWidth, m_windowHeight;
	int m_focusID;												// which control 
	bool m_vis;

	std::vector<GUIwindow*> m_GUIchild;

	GUIwindow(LPDIRECT3DDEVICE9 device, int x, int y, int w, int h, std::string name = "") : device(device),
		m_x(x), m_y(y), m_windowWidth(w), m_windowHeight(h), m_name(name)
	{
		m_focusID = -1;
		D3DXCreateFont(device, h, h, 0, 1, FALSE, DEFAULT_CHARSET,
			OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, 0, "ÀŒÃÂ", &pFont);

		mouseX = mouseY = 0;
		m_vis = 1;
	}
	~GUIwindow();

	int AddButton(std::string name, int x, int y, int w, int h, std::string tx, char *up, char *down);
	int AddText(std::string name, int x, int y, int w, int h, char *bg);
	int AddStaticText(std::string name, int x, int y, int w, int h, std::string tx = "", char *bg = 0);
	void AddChildGUI(GUIwindow *p);
	GUIwindow * FindChildGUI(std:: string name);
	std::vector<GUIwindow*> * GetAllChildGUI() { return &m_GUIchild; }
	GUIcontrol* FindControl(std::string name, ControlType t);
	GUIcontrol* GetControl(int id);
	void DeleteControl(int id);


	void ProcessMSG(UINT imsg, WPARAM wparam, LPARAM lparam);
	void ProcessKey(WPARAM wparam, LPARAM lparam);
	void ProcessMouse(int x, int y, bool isdown);


	void setVis(bool v);
	void OnRender();
	void OnUpdate();

	typedef void(*EventPtr)(GUIwindow *window);
	std::vector<EventPtr> m_events;
	void AddEvent(EventPtr p);
};

