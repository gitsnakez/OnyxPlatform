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

    // Transform the vertex position to clip space
    output.position = mul(input.position, m_world);
    output.position = mul(output.position, m_view);
    output.position = mul(output.position, m_proj);

    // Calculate the direction to the camera
    output.direction_to_camera = normalize(m_camera_position.xyz - output.position.xyz);

    // Calculate the TBN matrix
    output.tbn[0] = normalize(mul(input.tangent, m_world));
    output.tbn[1] = normalize(mul(input.binormal, m_world));
    output.tbn[2] = normalize(mul(input.normal, m_world));

    // Pass through texture coordinates
    output.texcoord = input.texcoord;

    return output;
}
