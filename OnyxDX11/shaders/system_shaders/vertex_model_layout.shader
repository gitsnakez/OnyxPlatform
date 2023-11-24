// Test shader for engine
// 				by snakEZ

Texture2D Material: register(t0);
sampler MaterialSampler: register(s0);

//
// Vertex shader section
//

struct VS_INPUT
{
	float4 position: POSITION0;
	float2 texcoord: TEXCOORD0;
	float3 normal:	 NORMAL0;
};

struct VS_OUTPUT
{
	float4 position: SV_POSITION;
	float2 texcoord: TEXCOORD0;
};

VS_OUTPUT vlsmain(VS_INPUT input)
{
	VS_OUTPUT output = (VS_OUTPUT)0;
	return output;
}