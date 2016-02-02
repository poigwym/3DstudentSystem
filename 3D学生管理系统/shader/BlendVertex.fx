
// 点光源
vector lightpos : LIGHTPOS;
float4 lightcolor = { 0, 0, 1.0f, 1.0f };

matrix WorldMat : WORLD;
shared matrix ViewProjMat : VIEWPROJ;


struct VS_INPUT {
	float4 pos : POSITION;
	float2 tex : TEXCOORD;
	float3 n : NORMAL;
};
struct VS_OUTPUT
{
	float4 pos : POSITION;
	float2 tex: TEXCOORD0;
	float  shade : TEXCOORD1;
};

VS_OUTPUT VS_Lighting(VS_INPUT input) {
	VS_OUTPUT output = (VS_OUTPUT)0;
	float4 worldpos = mul(input.pos, WorldMat);
	output.pos = mul(worldpos, ViewProjMat);
	output.tex = input.tex;
	input.n = normalize(mul(input.n, WorldMat));
	output.shade = saturate(dot(input.n, lightpos - worldpos));
	return output;
}


Texture texDiffuse;

sampler DiffuseSampler = sampler_state
{
	Texture = <texDiffuse>;
	MinFilter = Linear;
	MagFilter = Linear;
	MipFilter = Linear;
	AddressU = Wrap;
	AddressV = Wrap;
	AddressW = Wrap;
	MaxAnisotropy = 16;
};

float4 PS_Lighting(VS_OUTPUT input) : COLOR
{
	float4 color = tex2D(DiffuseSampler, input.tex);
	return color*input.shade;
	return color;
}


// 高光特效
technique Lighting
{
	pass P0
	{
		//Lighting = 0;   // ???
		vertexshader = compile vs_2_0 VS_Lighting();
		pixelshader = compile ps_2_0 PS_Lighting();
	}
}


// --------------------------------------------------
float4 PS_Shadow(VS_OUTPUT input) :COLOR{
	return float4(0.3f, 0.3f, 0.3f, 1.0f);
}

//shadow 特效
technique Shadow {
	pass P0 {
		//Lighting = 0;
		VertexShader = compile vs_2_0 VS_Lighting();
		PixelShader = compile ps_2_0 PS_Shadow();
	}
}



// ------------------------ skin mesh ----------------------------
matrix FinalTransforms[35];
int InfluenceNum = 2;

struct VS_INPUT_SKIN {
	float4 pos : POSITION;
	float3 n : NORMAL;
	float2 tex : TEXCOORD;
	float4 w : BLENDWEIGHT;
	int4  index : BLENDINDICES;
};

struct VS_OUTPUT_SKIN {
	float4 pos : POSITION;
	float2 tex : TEXCOORD0;
	float shade : TEXCOORD1;
};

VS_OUTPUT_SKIN VS_Skin(VS_INPUT_SKIN input) {
	VS_OUTPUT_SKIN output = (VS_OUTPUT)0;

	int n = InfluenceNum - 1;
	float tw = 0;
	float4 pos = { 0, 0, 0, 1 };
	float3 normal = { 0, 0, 0 };
  input.n = normalize(input.n);
	for (int i = 0;i<n;++i) {
		tw += input.w[i];
		pos += input.w[i] * mul(input.pos, FinalTransforms[input.index[i]]);
		normal += input.w[i] * mul(input.n, FinalTransforms[input.index[i]]);
	}
	tw = 1.0f - tw;
	pos += tw * mul(input.pos, FinalTransforms[input.index[n]]);
	pos.w = 1.0f;
	normal += tw * mul(input.n, FinalTransforms[input.index[n]]);

	float4 worldpos = mul(pos, WorldMat);
	float3 worldnormal = normalize(mul(normal, WorldMat));
	output.pos = mul(worldpos, ViewProjMat);
	output.tex = input.tex;
	output.shade = saturate(dot(worldnormal, normalize(lightpos - worldpos)));
	return output;
}

technique Skinlighting {

	pass P1 {
		Lighting = 0;
		vertexshader = compile vs_2_0 VS_Skin();
		pixelshader = compile  ps_2_0 PS_Lighting();
	}
}




