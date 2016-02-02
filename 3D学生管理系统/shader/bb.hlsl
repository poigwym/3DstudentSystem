


// µ„π‚‘¥
float4 lightcolor = { 0, 0, 1.0f, 1.0f };

struct PS_INPUT {
	vector pos : POSITION;
	vector n : TEXCOORD0;
	vector light : TEXCOORD1;
	float2 tex : TEXCOORD2;
};

sampler DiffuseSampler = sampler_state
{
	Texture = (texDiffuse);
	MinFilter = Linear;
	MagFilter = Linear;
	MipFilter = Linear;
	AddressU = Wrap;
	AddressV = Wrap;
	AddressW = Wrap;
	MaxAnisotropy = 16;
};


float4 PS_Main(
							in float3 normal:TEXCOORD1,
						  in float4 lightdir: TEXCOORD2,
							in float2 tex : TEXCOORD0 ) : COLOR
{
	vector color = tex2D(DiffuseSampler, tex);
  float angle = saturate(dot(normal, lightdir.xyz));
	return color+(lightcolor*angle);
}