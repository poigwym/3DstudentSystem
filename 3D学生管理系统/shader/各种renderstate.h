#pragma once


void render() {
	d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 150, 100), 1.0f, 0);
	d3dDevice->BeginScene();
	//close ligh：t
	d3dDevice->SetRenderState(D3DRS_LIGHTING, 0);   

	// camerma
	SetupMatrices();

	d3dDevice->EndScene();
	d3dDevice->Present(NULL, NULL, NULL, NULL);
}


void renderstate(LPDIRECT3DDEVICE9 d3dDevice) {

	// 线框-实体模式
	d3dDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	d3dDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

	// 着色模式
	d3dDevice->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD); // 插值
	d3dDevice->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_FLAT);

	// 背面消除
	d3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);  // 逆时针
	d3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);  // 顺时针
	d3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);  // 关闭消除


																														// 光照模式
	d3dDevice->LightEnable(0, true);    //  开光源
	d3dDevice->SetRenderState(D3DRS_LIGHTING, 1);    // 开光照

																									 // alpha 混合模式
																									 // 开启Alpha融合  
	d3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	//设置融合因子  
	//当前渲染对象的混合因子设置为这个对象的alpha通道
	d3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//目标（后台缓存）混合因子设为源alpha的逆
	d3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	//设置融合运算方式  
	d3dDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
}

