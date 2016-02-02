
matrix WorldMat;
matrix ViewProjMat;
matrix ViewMat;
vector lightdir;
vector lightcolor;


struct VS_INPUT {
	vector pos: POSITION;
	vector normal : NORMAL;
};

struct VS_OUTPUT {
	vector pos : POSITION;
	float2 uv :  TEXCOORD;
	vector diffuse  : COLOR;
};

VS_OUTPUT VS_Main(VS_INPUT input) {
	VS_OUTPUT output = (VS_OUTPUT)0;

	input.pos = mul(input.pos, WorldMat);
	output.pos = mul(input.pos, ViewProjMat);
	output.diffuse = lightcolor;


	// 相机坐标下 
	// 光线向量和点法线的夹角作为纹理坐标的u
	input.normal.w = 0;
	input.normal = mul(input.normal, ViewMat);
	vector _lightdir = lightdir;
	_lightdir.w = 0;
	_lightdir = mul(_lightdir, ViewMat);
	float u = dot(input.normal, _lightdir);
	if(u < 0.0f)
		u = 0.0f;

	output.uv.x = u;
	output.uv.y = 0.5f;

	return output;
}
	

