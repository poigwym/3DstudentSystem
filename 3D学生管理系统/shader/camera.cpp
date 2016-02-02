

#include"camera.h"

Camera::Camera(IDirect3DDevice9 *d3dDevice, int w, int h) :d3dDevice(d3dDevice), width(w), height(h)
{
	vec[rig] = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	vec[up] = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vec[fore] = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

	projmat = new D3DXMATRIX;
	viewmat = new D3DXMATRIX;

	SetProj();
	SetViewport();
}

 void Camera::Update(D3DXVECTOR3 eyepoint, D3DXVECTOR3 lookat)
{
	eye = eyepoint;
	tar = lookat;

	vec[2] = tar - eye;
	D3DXVec3Normalize(vec + 2, vec + 2);
	D3DXVec3Cross(vec, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), vec + 2);
	D3DXVec3Normalize(vec, vec);
	D3DXVec3Cross(vec + 1, vec + 2, vec);
	D3DXVec3Normalize(vec + 1, vec + 1);

	SetView();
}

void Camera::SetEye(float x, float y, float z) {
	eye = D3DXVECTOR3(x, y, z);
	tar = eye + vec[fore] * 50;
	Update(eye, tar);
}

void Camera::SetTar(float x, float y, float z) {
	tar = D3DXVECTOR3(x, y, z);
	Update(eye, tar);
}

void Camera::GetEye(float *x, float *y, float *z) {
	if (x) *x = eye.x;
	if (y) *y = eye.y;
	if (z) *z = eye.z;
}

void Camera::GetTar(float *x, float *y, float *z) {
	if (x) *x = tar.x;
	if (y) *y = tar.y;
	if (z) *z = tar.z;
}

void Camera::move(float dx, float dy, float dz) {
	eye = eye + dz*vec[fore];
	eye = eye + dx*vec[rig];
	eye = eye + dy*vec[up];

	tar = eye + vec[fore] * 50;
	Update(eye, tar);
}

 void Camera::rot(int p, float d) {
	if (fabs(d) < 0.0001) return;

	if (p == up)
	{
		D3DXMATRIX rotmat;
		D3DXMatrixRotationAxis(&rotmat, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), d);
		D3DXVec3TransformNormal(&vec[fore], &vec[fore], &rotmat);
		D3DXVec3TransformNormal(&vec[rig], &vec[rig], &rotmat);
	}
	else  if (p == rig)
	{
		D3DXMATRIX rotmat;
		D3DXMatrixRotationAxis(&rotmat, &vec[rig], d);
		D3DXVec3TransformNormal(&vec[fore], &vec[fore], &rotmat);
		D3DXVec3TransformNormal(&vec[up], &vec[up], &rotmat);
	}
	tar = eye + 50 * vec[fore];
	Update(eye, tar);
}

D3DXMATRIX Camera::GetView() {
	return *viewmat;
}
D3DXMATRIX Camera::GetProj() {
	return  *projmat;
}

void Camera::SetView() {

	*viewmat = D3DXMATRIX(vec[0].x, vec[1].x, vec[2].x, 0,
		vec[0].y, vec[1].y, vec[2].y, 0,
		vec[0].z, vec[1].z, vec[2].z, 0,
		-(eye.x*vec[0].x + eye.y*vec[0].y + eye.z*vec[0].z),
		-(eye.x*vec[1].x + eye.y*vec[1].y + eye.z*vec[1].z),
		-(eye.x*vec[2].x + eye.y*vec[2].y + eye.z*vec[2].z), 1);
	d3dDevice->SetTransform(D3DTS_VIEW, viewmat);
}

void Camera::SetProj() {
	D3DXMatrixPerspectiveFovLH(projmat, D3DX_PI / 4, (float)width / height, 1.0f, 300.0f);
	d3dDevice->SetTransform(D3DTS_PROJECTION, projmat);
}

void Camera::SetViewport() {
	D3DVIEWPORT9 vp = { 0, 0, width, height, 0, 1 };
	d3dDevice->SetViewport(&vp);
}