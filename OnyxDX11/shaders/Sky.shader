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
	return Material.Sample(MaterialSampler, 1.0 - input.texcoord);
}