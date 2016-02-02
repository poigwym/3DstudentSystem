



// 点光源
vector lightpos : LIGHTPOS;
float4 lightcolor = { 0, 0, 1.0f, 1.0f };


matrix WorldMat : WORLD;
matrix ViewProjMat : VIEWPROJ;

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
	output.shade = saturate(dot(input.n, lightpos-worldpos));
	return output;
}
sampler DiffuseSampler = sampler_state
{
	//Texture = (texDiffuse);
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
}


// 高光特效
technique Lighting
{
	pass P0
	{
		//Lighting = 0;   // ???
		vertexshader  = compile vs_2_0 VS_Lighting();
		pixelshader  = compile ps_2_0 PS_Lighting();
	}
}


// --------------------------------------------------
float4 PS_Shadow(VS_OUTPUT input) :COLOR {
	return float4(0.3f, 0.3f, 0.3f, 1.0f);
}

// shadow 特效
technique Shadow {
	pass P0 {
		//Lighting = 0;
		VertexShader = compile vs_2_0 VS_Lighting();
		PixelShader = compile ps_2_0 PS_Shadow();
	}
}




