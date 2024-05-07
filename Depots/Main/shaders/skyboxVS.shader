struct VS_INPUT
{
    float4 position: POSITION0;
    float2 texcoord: TEXCOORD0;
    float3 normal: NORMAL0;
    float3 tangent: TANGENT0;
    float3 binormal: BINORMAL0;
};



struct VS_OUTPUT
{
    float4 position: SV_POSITION;
    float2 texcoord: TEXCOORD0;
    float3 direction_to_camera: TEXCOORD1;
    row_major float3x3 tbn: TEXCOORD2;
};



cbuffer constant: register(b0)
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



VS_OUTPUT vsmain(VS_INPUT input)
{
    VS_OUTPUT output;

    // Transform vertex position from object space to clip space
    output.position = mul(input.position, m_world); // Transform to world space
    output.position = mul(output.position, m_view); // Transform to view space
    output.position = mul(output.position, m_proj); // Transform to clip space

    // Pass through texture coordinates
    output.texcoord = input.texcoord;

    // Calculate direction from vertex to camera in view space
    output.direction_to_camera = m_camera_position.xyz - output.position.xyz;

    // Calculate TBN matrix (tangent, binormal, normal)
    output.tbn = row_major(float3x3(input.tangent, input.binormal, input.normal));

    return output;
}