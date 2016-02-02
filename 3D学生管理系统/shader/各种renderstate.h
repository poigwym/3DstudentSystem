#pragma once


void render() {
	d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 150, 100), 1.0f, 0);
	d3dDevice->BeginScene();
	//close ligh��t
	d3dDevice->SetRenderState(D3DRS_LIGHTING, 0);   

	// camerma
	SetupMatrices();

	d3dDevice->EndScene();
	d3dDevice->Present(NULL, NULL, NULL, NULL);
}


void renderstate(LPDIRECT3DDEVICE9 d3dDevice) {

	// �߿�-ʵ��ģʽ
	d3dDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	d3dDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

	// ��ɫģʽ
	d3dDevice->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD); // ��ֵ
	d3dDevice->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_FLAT);

	// ��������
	d3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);  // ��ʱ��
	d3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);  // ˳ʱ��
	d3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);  // �ر�����


																														// ����ģʽ
	d3dDevice->LightEnable(0, true);    //  ����Դ
	d3dDevice->SetRenderState(D3DRS_LIGHTING, 1);    // ������

																									 // alpha ���ģʽ
																									 // ����Alpha�ں�  
	d3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	//�����ں�����  
	//��ǰ��Ⱦ����Ļ����������Ϊ��������alphaͨ��
	d3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//Ŀ�꣨��̨���棩���������ΪԴalpha����
	d3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	//�����ں����㷽ʽ  
	d3dDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
}

