


// µ„π‚‘¥
vector lightpos;

matrix WorldViewMat;
matrix WorldViewProjMat;

struct VS_INPUT {
	float4 pos : POSITION;
	float2 tex : TEXCOORD;
	float3 n : NORMAL;
};
struct VS_OUTPUT
{
	float4 pos : POSITION;
	float2 tex: TEXCOORD0;
	float3 n: TEXCOORD1;
	float3 light: TEXCOORD2;
};
VS_OUTPUT VS_Main(VS_INPUT input) {
	VS_OUTPUT output = (VS_OUTPUT)0;
	output.pos = mul(input.pos, WorldViewProjMat);
	output.tex = input.tex;
	output.n = input.n;
	// output.n = mul(input.n, worldmat);
	vector dir;
	output.light = lightpos - input.pos;
	output.light = normalize(output.light);
	return output;
}
