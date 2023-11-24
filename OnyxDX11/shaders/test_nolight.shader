// Test shader for engine
// 				by snakEZ

Texture2D Material: register(t0);
sampler MaterialSampler: register(s0);

cbuffer constant: register(b0)
{
	row_major float4x4 m_world;
	row_major float4x4 m_view;
	row_major float4x4 m_proj;
	float4 m_light_direction;
	float4 m_camera_position;
};

//
// Vertex shader section
//

struct VS_INPUT
{
	float4 position: POSITION0;
	float2 texcoord: TEXCOORD0;
	float3 normal:	 TEXCOORD1;
};

struct VS_OUTPUT
{
	float4 position: SV_POSITION;
	float2 texcoord: TEXCOORD0;
	float3 normal:	 TEXCOORD1;
};

VS_OUTPUT vsmain(VS_INPUT input)
{
	VS_OUTPUT output = (VS_OUTPUT)0;

	//	output.position = lerp(input.position, input.position1, (float)((sin((float)(m_time / (float)1000.0f)) + 1.0f) / 2.0f));

	//WORLD SPACE
	output.position = mul(input.position, m_world);

	//VIEW SPACE
	output.position = mul(output.position, m_view);

	//SCREEN SPACE
	output.position = mul(output.position, m_proj);


	output.texcoord = input.texcoord;
	output.normal = input.normal;
	return output;
}

//
// Pixel shader section
//

struct PS_INPUT
{
	float4 position: SV_POSITION;
	float2 texcoord: TEXCOORD0;
	float3 normal:	 TEXCOORD1;
};

float4 psmain(PS_INPUT input) : SV_TARGET
{
	return Material.Sample(MaterialSampler, input.texcoord);
}