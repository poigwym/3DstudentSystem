



static vector black = { 0.0f, 0.0f, 0.0f, 1.0f };

extern matrix WorldViewMat;
extern matrix ProjMat;


struct VS_INPUT {
	vector pos : POSITION;
	vector n : NORMAL0;
	vector n1 : NORMAL1;
	vector n2 : NORMAL2;
};


struct VS_OUTPUT {
	vector pos : POSITION;
	vector color : COLOR;
};
//

VS_OUTPUT VS_Main(VS_INPUT input) {
	VS_OUTPUT output  = (VS_OUTPUT)0;

	input.n.w = input.n1.w = input.n2.w = 0.0f;
	input.pos = mul(input.pos, WorldViewMat);
	vector dir = input.pos;
	vector n1 = mul(input.n1, WorldViewMat);
	vector n2 = mul(input.n2, WorldViewMat);
	// edge which between two faces that is not in same dir  is outline
	if((dot(dir, n1)*dot(dir, n2)) < 0) {
		input.pos += 0.1f * input.n;
	}

	output.pos = mul(input.pos, ProjMat);
	output.color  = black;
	return output;

}

