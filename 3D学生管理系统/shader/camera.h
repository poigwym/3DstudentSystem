
#pragma once
#include<D3dx9math.h>
#include<d3dx9.h>
#include<d3d9.h>


#define RELEASE(x) { if(x) (x)->Release(); x=0; }
#define DELETE(x) { if(x) delete x; x=0;}	

struct Camera {
	enum { rig, up, fore };
	D3DXVECTOR3  vec[3];
	D3DXVECTOR3  eye, tar;
	IDirect3DDevice9 *d3dDevice;
	int width, height;

	D3DXMATRIX *projmat, *viewmat;

	Camera(IDirect3DDevice9 *d3dDevice, int w, int h);
	void Update(D3DXVECTOR3 eyepoint, D3DXVECTOR3 lookat);
	void SetEye(float x,float y,float z);
	void SetTar(float x,float y,float z);
	void GetEye(float *x, float *y, float *z);
	void GetTar(float *x, float *y, float *z);
	void move(float dx, float dy, float dz);
	void rot(int p, float d);
	
	void SetView();
	void SetProj();
	void SetViewport();

	D3DXMATRIX GetView();
	D3DXMATRIX GetProj();
	/*inline	void CalPickRay(float x, float y, Ray3D *ray) {
		if(!projmat) SetProj();
		float px = (2*x/width-1) / (*projmat)(0,0);
		float py = (-2*y/height+1) / (*projmat)(1,1);

		if(!viewmat) SetView();
		D3DXMATRIX inviewmat;
		D3DXMatrixInverse(&inviewmat,	0, viewmat);
		D3DXVECTOR3 p0 = D3DXVECTOR3(0,0,0);
		D3DXVECTOR3 dir = D3DXVECTOR3(px, py, 1.0f);

		D3DXVec3TransformCoord(&p0, &p0, &inviewmat);
		D3DXVec3TransformNormal(&dir,&dir,&inviewmat);

		ray->p0 = vector3D(p0.x, p0.y, p0.z);
		ray->dir = vector3D(dir.x, dir.y, dir.z);
	}
*/
	
	~Camera() {
		DELETE(viewmat);
		DELETE(projmat);
	}
};



//ÓÃ·¨£º
//camera = new Camera(d3dDevice, WID, HEI);
//camera->SetEye(0, 0, -50);
//camera->SetTar(0, 0, 0);
//camera->SetView();
//camera->SetProj();
//camera->SetViewport();
//dxinput->update();
//if (dxinput->KeyDown(DIK_A)) camera->move(-0.1f, 0, 0);
//else if (dxinput->KeyDown(DIK_D))camera->move(0.1f, 0, 0);
//else if (dxinput->KeyDown(DIK_W))camera->move(0, 0, 0.1f);
//else if (dxinput->KeyDown(DIK_S))camera->move(0, 0, -0.1f);
//camera->rot(Camera::up, 0.01*dxinput->GetMouseX());
//camera->rot(Camera::rig, 0.01*dxinput->GetMouseY());

//CalPickRay(x, y, &ray); //Ê°È¡