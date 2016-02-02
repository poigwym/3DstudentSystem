#pragma once


#include"d3dutil.h"


void SetupMatrices()
{
	//word
	D3DXMATRIX matworld;
	D3DXMatrixTranslation(&matworld, 0, 0, 0);
	//d3dDevice->SetTransform(D3DTS_WORLD, &matworld);

	//camara
	D3DXVECTOR3 vEyePt(0, 0, -200);
	D3DXVECTOR3 vLookatPt(0, 0, 0);
	D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);
	D3DXMATRIX matView;
	D3DXMatrixLookAtLH(&matView, &vEyePt, &vLookatPt, &vUpVec);
	d3dDevice->SetTransform(D3DTS_VIEW, &matView);

	//projection
	D3DXMATRIX matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4, 1.0f, 1.0f, 1000.0f);
	d3dDevice->SetTransform(D3DTS_PROJECTION, &matProj);
	//viewport
	D3DVIEWPORT9 vp = { 0, 0, WID, HEI, 0, 1 };  
	d3dDevice->SetViewport(&vp);
}

