//
//#include"d3dutil.h"
//#include"animation.h"
//#include"camara.h"
//#include"inputsystem.h"
//using namespace d3d;
//
//
//// -----------------shader base ------------------------
//struct Shader {
//	LPDIRECT3DDEVICE9 d3dDevice;
//	ID3DXConstantTable *ConstTable;
//
//	Shader() { memset(this, 0, sizeof(*this)); }
//	Shader(LPDIRECT3DDEVICE9 _d3dDevice) : d3dDevice(_d3dDevice) {}
//	virtual ~Shader() {}
//	virtual void init() {}
//	virtual void render() {}
//};
//
//// ------------------- vertex shader ---------------------
//struct VertexShader : public Shader {
//
//	IDirect3DVertexShader9 *vs;
//	D3DXHANDLE  hViewProjMat, hWorldViewMat;
//	VertexShader() { }
//	VertexShader(LPDIRECT3DDEVICE9 _d3dDevice) :Shader(_d3dDevice) {}
//	virtual ~VertexShader() {
//		RELEASE(vs);
//		RELEASE(hViewProjMat);
//		RELEASE(hWorldViewMat);
//	}
//	virtual void init() {
//		HRESULT hr;
//		ID3DXBuffer *shader = 0;
//		ID3DXBuffer *errorbuffer = 0;
//
//		// vertexshader 入口函数
//		//编译， 创建缓存, 常量表
//		hr = D3DXCompileShaderFromFile("aa.hlsl",
//			0, 0, "VS_Main", "vs_2_0", D3DXSHADER_DEBUG,
//			&shader, &errorbuffer, &ConstTable);
//		if (FAILED(hr)) {
//			MessageBox(0, (char*)errorbuffer->GetBufferPointer(), 0, 0);
//			return;
//		}
//
//		// 创建 vertex shader
//		hr = d3dDevice->CreateVertexShader((DWORD*)shader->GetBufferPointer(), &vs);
//		if (FAILED(hr)) {
//			MessageBox(0, "create vs fail", 0, 0);
//			return;
//		}
//		RELEASE(shader);
//
//		ConstTable->SetDefaults(d3dDevice);
//
//		hViewProjMat = ConstTable->GetConstantByName(0, "WorldViewProjMat");
//		hlightpos = ConstTable->GetConstantByName(0, "lightpos");
//
//
//	}
//	virtual void render() {
//		// 矩阵放到顶点着色器
//		ConstTable->SetMatrix(d3dDevice, hViewProjMat, &viewproj);
//		// output
//		d3dDevice->SetVertexShader(vs);
//	}
//};
//
//
//// -------------------------- pixel shader---------------------
//struct PixelShader : public Shader {
//
//	IDirect3DPixelShader9 *ps;
//	PixelShader() { }
//	PixelShader(LPDIRECT3DDEVICE9 _d3dDevice) :Shader(_d3dDevice) {}
//	virtual ~PixelShader() {
//		RELEASE(ps);
//	}
//	virtual void init() {
//		HRESULT hr;
//		ID3DXBuffer *shader = 0;
//		ID3DXBuffer *errorbuffer = 0;
//
//		// vertexshader 入口函数
//		//编译， 创建缓存, 常量表
//		hr = D3DXCompileShaderFromFile("bb.hlsl",
//			0, 0, "PS_Main", "ps_2_0", D3DXSHADER_DEBUG,
//			&shader, &errorbuffer, &ConstTable);
//		if (FAILED(hr)) {
//			MessageBox(0, (char*)errorbuffer->GetBufferPointer(), 0, 0);
//			return;
//		}
//		if (!d3dDevice) return;
//		// 创建 vertex shader
//		hr = d3dDevice->CreatePixelShader((DWORD*)shader->GetBufferPointer(), &ps);
//		if (FAILED(hr)) {
//			MessageBox(0, "create ps fail", 0, 0);
//			return;
//		}
//		RELEASE(shader);
//		ConstTable->SetDefaults(d3dDevice);
//	}
//	virtual void render() {
//		d3dDevice->SetPixelShader(ps);
//	}
//};
//

// ----------------------- effect shader ----------------------------
//struct EffectShader : public Shader {
//	ID3DXEffect *es;
//	ID3DXBuffer *errorbuf;
//	D3DXHANDLE hW, hVP;
//	EffectShader(LPDIRECT3DDEVICE9 d3dDevice, const char*filename) :Shader(d3dDevice) {
//		if (FAILED(D3DXCreateEffectFromFile(d3dDevice, filename, 0, 0, 0, 0, &es, &errorbuf)))
//		{
//			mout((char*)errorbuf->GetBufferPointer());
//			exit(1);
//			return;
//		}
//		hW = es->GetParameterBySemantic(0, "WORLD");
//		hVP = es->GetParameterBySemantic(0, "VIEWPROJ");
//
//	}
//
//	void render() {
//		es->SetTechnique("Lighting");
//		D3DXMATRIX viewproj, world;
//		D3DXMatrixIdentity(&world);
//		es->SetMatrix(hW, &world);
//		//viewproj = camera->GetView()*camera->GetProj();
//		es->SetMatrix(hVP, &viewproj);
//		UINT c;
//
//		es->Begin(&c, 0);
//		for (int i = 0;i<c;++i) {
//			es->BeginPass(i);
//			es->CommitChanges();
//			//teapot->DrawSubset(0);
//			es->EndPass();
//		}
//		es->End();
//	}
//};