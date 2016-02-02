
#include"GUIstaticText.h"






void GUIstaticText::SetBounding(char *file)
{
	if (FAILED(D3DXCreateTextureFromFile(device, file, &bounding)))
		exit(1);
}

void GUIstaticText::OnRender()
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
	pFont->DrawText(0, m_text.c_str(), m_text.length(), &Rct, DT_LEFT, D3DCOLOR_XRGB(0, 0, 0));
}



GUIstaticText::~GUIstaticText()
{
	if (bounding) bounding->Release();
}
