

#include"GUITextBox.h"


GUItext::GUItext(LPDIRECT3DDEVICE9 Device, int w, int h, std::string name) : GUIcontrol(Device, w, h, name)
{
	D3DXCreateFont(device, h, h, 0, 1, FALSE, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, 0, "ËÎÌו", &pFont);


	D3DXCreateLine(Device, &m_CaretLine);

	ZeroMemory(m_CaretVector, sizeof(D3DXVECTOR2)* 2);
	m_TextWidth = 0.0f;
	m_Text = "";
	m_CaretVisible = false;
	CaretCharPos = 0;
	bounding = 0;
}

FLOAT GUItext::GetStringWidth(std::string String)
{
	RECT String_Info;
	ZeroMemory(&String_Info, sizeof(RECT));
	if (pFont)
		pFont->DrawText(NULL, String.c_str(), String.length(),
		&String_Info, DT_CALCRECT, D3DCOLOR_XRGB(0, 0, 0));
	return String_Info.right;
}
FLOAT GUItext::GetStringHeight(std::string String)
{
	RECT String_Info;
	ZeroMemory(&String_Info, sizeof(RECT));
	if (pFont)
		pFont->DrawText(NULL, String.c_str(), String.length(),
		&String_Info, DT_CALCRECT, D3DCOLOR_XRGB(0, 0, 0));
	return String_Info.bottom;
}

void GUItext::SetText(std::string tx)
{
	int Width = GetStringWidth(tx);
	if (Width <= GetWidth())
	{
		m_Text = tx;
		m_TextWidth = Width;
		SetCaretPos(max(0, (int)tx.length()-1));
	}
}

void GUItext::SetCaretPos(long Pos)
{
	if ((Pos >= 0) && (Pos <= m_Text.length()))
	{
		std::string tmpstr = m_Text.substr(0, Pos);
		//Top of line
		m_CaretVector[0].x = GetStringWidth(tmpstr); //Set X Pos
		//Bottom of line
		m_CaretVector[1].x = m_CaretVector[0].x;
		CaretCharPos = Pos;
	}
}
bool GUItext::InsertText(char* Text)
{
	std::string TmpStr = Text;
	if ((m_TextWidth + GetStringWidth(TmpStr)) <= GetWidth())
	{
		m_Text.insert(CaretCharPos, Text);
		m_TextWidth = GetStringWidth(m_Text);
		SetCaretPos(GetCaretPos() + strlen(Text));
		return true;
	}
	return false;
}
long GUItext::RemoveText(long Quantity)
{
	SetCaretPos(GetCaretPos() - Quantity);
	m_Text.erase(CaretCharPos, Quantity);
	m_TextWidth = GetStringWidth(m_Text);
	return m_TextWidth;
}
void GUItext::OnKeyDown(WPARAM Key, LPARAM Extended)
{
	switch (Key)
	{
	case VK_BACK:
	case VK_DELETE:
	{
									RemoveText(1);
	}
		break;
	case VK_LEFT:
	{
								SetCaretPos(GetCaretPos() - 1);
	}
		break;
	case VK_RIGHT:
	{
								 SetCaretPos(GetCaretPos() + 1);
	}
		break;
	default:
	{
					 if( ('0' <= Key && Key <= '9') ||  ('a' <= Key && Key <= 'z' ) || 
						   ('A' <= Key && Key <= 'Z'))
					 InsertText((char*)&Key);
	}
	}
}

bool GUItext::CursorIntersectChar(int X, int Y)
{
	if ((X >= m_x) && (X <= m_x + m_TextWidth))
	if ((Y >= m_y) && (Y <= m_y + GetHeight()))
		return true;
	return false;
}

long GUItext::GetCharAtPos(int X, int Y)
{
	long Pos = 0;
	long Left = 0;
	long Right = 0;
	Left = m_x;
	while (Pos < m_Text.length())
	{
		std::string TmpStr = m_Text.substr(Pos, 1);
		Right = GetStringWidth(TmpStr);
		if ((X >= Left) && (X <= Left + Right))
			break;
		Pos++;
		Left += Right;
	}
	return Pos;
}

void GUItext::OnMouseDown(int isdown, int X, int Y)
{
	if (isdown)
		if (CursorIntersectChar(X, Y))
			SetCaretPos(GetCharAtPos(X, Y));
}


void GUItext::OnMouseMove(int X, int Y)
{
}

void GUItext::OnMouseUp(int Button, int X, int Y){
}

void GUItext::OnSetFocus(){
}

void GUItext::OnLostFocus() {
}

void GUItext::OnKeyUp(WPARAM Key, LPARAM Extended)
{
}


void GUItext::OnRender()
{
	if (!m_vis)
		return;



	if (bounding) {
		GUIVTX vtx[] = {
			GUIVTX(m_x, m_y + GetHeight(), 0.0f, 1.0f, D3DCOLOR_XRGB(255,255,255), 0.0f, 1.0f),
			GUIVTX(m_x, m_y, 0.0f, 1.0f, D3DCOLOR_XRGB(255, 255, 255), 0.0f, 0.0f),
			GUIVTX(m_x + GetWidth(), m_y + GetHeight(), 0.0f, 1.0f, D3DCOLOR_XRGB(255, 255, 255), 1.0f, 1.0f),
			GUIVTX(m_x + GetWidth(), m_y, 0.0f, 1.0f, D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0.0f),
		};


		// alpha blend
		// op = add
		device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
		device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		device->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		device->SetFVF(GUIVTX::FVF);
		device->SetTexture(0, bounding);
		device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vtx, sizeof(GUIVTX));
		device->SetRenderState(D3DRS_ALPHABLENDENABLE, 0);

	}


	RECT Rct;
	Rct.left = m_x;
	Rct.top = m_y;
	Rct.right = m_x + GetWidth();
	Rct.bottom = m_y + GetHeight();

	if (m_name == "LoginKey")
	{
		int len = m_Text.length();
		std::string key(len, '*');
		pFont->DrawText(0, key.c_str(), key.length(), &Rct, DT_LEFT, D3DCOLOR_XRGB(0, 0, 0));
	}

	else 
		pFont->DrawText(0, m_Text.c_str(), m_Text.length(), &Rct, DT_LEFT, D3DCOLOR_XRGB(0, 0, 0));
	if (m_focus)
	if (m_CaretVisible)
	{
		GUIVTX Line[] = {
			GUIVTX(m_x + m_CaretVector[0].x, m_y + m_CaretVector[0].y, 0, 1, D3DCOLOR_XRGB(0, 0, 0), 0, 0),
			GUIVTX(m_x + m_CaretVector[0].x, m_y + m_CaretVector[0].y + GetHeight(), 0, 1, D3DCOLOR_XRGB(0, 0, 0), 0, 0)
		};
		device->SetFVF(GUIVTX::FVF);
		device->DrawPrimitiveUP(D3DPT_LINESTRIP, 1, &Line[0], sizeof(GUIVTX));

		m_CaretVisible = false;
	}
	else
		m_CaretVisible = true;
}

GUItext::~GUItext()
{
	if (m_CaretLine)
		m_CaretLine->Release();

	if (bounding)
		bounding->Release();
}


void GUItext::SetBounding(char *file)
{
	if (FAILED(D3DXCreateTextureFromFile(device, file, &bounding)))
		exit(1);

}

void GUItext::ProcessMouse(int x, int y, int isdown)
{
	OnMouseDown(isdown, x, y);
}

void GUItext::ProcessKey(WPARAM wparam, LPARAM lparam)
{
	OnKeyDown(wparam, lparam);
}