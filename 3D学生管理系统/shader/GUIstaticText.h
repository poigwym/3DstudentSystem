#include"GUIbase.h"


class GUIstaticText : public GUIcontrol
{
public:
	std::string m_text;
	LPDIRECT3DTEXTURE9 bounding;

	GUIstaticText(LPDIRECT3DDEVICE9 device, int w, int h, std::string name = "") : GUIcontrol(device, w, h, name) 
	{
		D3DXCreateFont(device, h, h, 0, 1, FALSE, DEFAULT_CHARSET,
			OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, 0, "ËÎÌו", &pFont);
		m_text = "";
		bounding = 0;
	}
	~GUIstaticText();

	void SetText(std::string tx) { m_text = tx; }
	void SetBounding(char *file);
	std::string GetText() { return m_text; }
	void OnRender();
	// msg
	virtual void ProcessMouse(int x, int y, int isdown) {}
	virtual void ProcessKey(WPARAM wparam, LPARAM lparam) {}
};
