
#pragma once

#include"GUIbase.h"



// ------------------------------ нд╠╬©Р ---------------------------------
class GUItext : public GUIcontrol
{
protected:
	std::string m_Text; //Actual text of the text box
	LPD3DXLINE m_CaretLine; //Caret line interface
	D3DXVECTOR2 m_CaretVector[2]; //Top and bottom points of the line
	bool m_CaretVisible; //Is line visible?
	long CaretCharPos; //Index of caret
	FLOAT m_TextWidth;

	LPDIRECT3DTEXTURE9 bounding;
public:
	GUItext(LPDIRECT3DDEVICE9 Device, int w, int h, std::string name = "");
	~GUItext();
	void OnRender();
	void OnMouseDown(int Button, int X, int Y);
	void OnMouseMove(int X, int Y);
	void OnMouseUp(int Button, int X, int Y);
	void OnSetFocus();
	void OnLostFocus();
	void OnKeyDown(WPARAM Key, LPARAM Extended);
	void OnKeyUp(WPARAM Key, LPARAM Extended);
	//void OnSysKey(WPARAM Key, LPARAM Extended);
	const char* GetText() const { return m_Text.c_str(); }
	void SetText(std::string tx);
	long GetCharAtPos(int X, int Y);
	bool CursorIntersectChar(int X, int Y);
	FLOAT GetStringWidth(std::string String);
	FLOAT GetStringHeight(std::string String);
	long GetCaretPos() const { return CaretCharPos; }
	void SetCaretPos(long Pos);
	bool InsertText(char* Text);
	long RemoveText(long Quantity);


	void SetBounding(char *file);
	virtual void ProcessMouse(int x, int y, int isdown);
	virtual void ProcessKey(WPARAM wparam, LPARAM lparam);
};

