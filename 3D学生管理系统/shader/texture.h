#pragma once


#include"d3dutil.h"

void Texture (LPDIRECT3DDEVICE9 d3dDevice) {

	LPDIRECT3DTEXTURE9 pTexture;			//�������
	D3DXCreateTextureFromFile(d3dDevice, L"file.jpg", &pTexture);	//����

	d3dDevice->SetTexture(0, pTexture);   		//��������`
}
