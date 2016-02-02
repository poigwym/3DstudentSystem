
#include"GUIbutton.h"


GUIbutton::GUIbutton(LPDIRECT3DDEVICE9 device, int w, int h, std::string name, std::string button) : 
		GUIcontrol(device, w, h, name) 
{
	D3DXCreateFont(device, h/3, h/3, 0, 1, FALSE, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, 0, "宋体", &pFont);


	m_isClick = false;
	m_buttonText = button;
	bounding = 0;
}


GUIbutton::~GUIbutton()
{
	if (bounding) {
		bounding->Release();
		bounding = 0;
	}
}




void GUIbutton::setBounding(char *file)
{
	if (FAILED(D3DXCreateTextureFromFile(device, file, &bounding)))
		exit(1);
}

void GUIbutton::setButtonText(std::string tx)
{
	m_buttonText = tx;
}


void GUIbutton::OnRender()
{

	if (!m_vis) return;

	if (bounding) {
		GUIVTX vtx[] = {
			GUIVTX(m_x, m_y + GetHeight(), 0.0f, 1.0f, D3DCOLOR_XRGB(255, 255, 255), 0.0f, 1.0f),
			GUIVTX(m_x, m_y, 0.0f, 1.0f, D3DCOLOR_XRGB(255, 255, 255), 0.0f, 0.0f),
			GUIVTX(m_x + GetWidth(), m_y + GetHeight(), 0.0f, 1.0f, D3DCOLOR_XRGB(255, 255, 255), 1.0f, 1.0f),
			GUIVTX(m_x + GetWidth(), m_y, 0.0f, 1.0f, D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0.0f),
		};


		// alpha blend
		// op = add
		//device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);// Alpha值是取自材质  
		//device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1); //将纹理颜色混合的第一个参数的ALPHA

		device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
		device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		device->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_MIN);

		device->SetFVF(GUIVTX::FVF);
		device->SetTexture(0, bounding);
		device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vtx, sizeof(GUIVTX));
		device->SetRenderState(D3DRS_ALPHABLENDENABLE, 0);

	}

	RECT rc;
	rc.left = m_x;
	rc.right = m_x + GetWidth();
	rc.top = m_y + GetHeight() / 3;
	rc.bottom = m_y + (GetHeight()) * 2 / 3;
	pFont->DrawText(0, m_buttonText.c_str(), m_buttonText.length(), &rc, DT_CENTER, D3DCOLOR_XRGB(0, 0, 0));
}



void GUIbutton::ProcessMouse(int x, int y, int isdown)
{
	m_isClick = isdown;
}

void GUIbutton::ProcessKey(WPARAM wparam, LPARAM lparam)
{
}