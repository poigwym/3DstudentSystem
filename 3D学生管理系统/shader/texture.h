#pragma once


#include"d3dutil.h"

void Texture (LPDIRECT3DDEVICE9 d3dDevice) {

	LPDIRECT3DTEXTURE9 pTexture;			//纹理对象
	D3DXCreateTextureFromFile(d3dDevice, L"file.jpg", &pTexture);	//创建

	d3dDevice->SetTexture(0, pTexture);   		//启用纹理`
}
