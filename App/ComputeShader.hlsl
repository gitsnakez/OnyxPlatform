Texture2D Color : register(t0);
sampler ColorSampler : register(s0);

Texture2D Normal : register(t1);
sampler NormalSampler : register(s1);



struct PS_INPUT
{
    float4 position : SV_POSITION;
    float2 texcoord : TEXCOORD0;
    float3 direction_to_camera : TEXCOORD1;
    row_major float3x3 tbn : TEXCOORD2;
};



cbuffer constant : register(b0)
{
    row_major float4x4 m_world;
    row_major float4x4 m_view;
    row_major float4x4 m_proj;
    float4 m_light_direction;
    float4 m_camera_position;
    float4 m_light_position;
    float m_light_radius;
    float m_time;
};



float4 psmain(PS_INPUT input) : SV_TARGET
{
    return Color.Sample(ColorSampler, float2(1.0 - input.texcoord.x, 1.0 - input.texcoord.y));
}
