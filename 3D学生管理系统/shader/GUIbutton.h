
#pragma once

#include"GUIbase.h"



class GUIbutton : public GUIcontrol
{
public:
	std::string m_buttonText;
	LPDIRECT3DTEXTURE9 bounding;
	bool m_isClick;
	GUIbutton(LPDIRECT3DDEVICE9 device, int w, int h, std::string name, std::string button);
	~GUIbutton();

	bool isClick() { return m_isClick; }
	void setBounding(char *file);
	void setButtonText(std::string tx);
	virtual void OnRender();
	virtual void ProcessMouse(int x, int y, int isdown);
	virtual void ProcessKey(WPARAM wparam, LPARAM lparam);

};
