Texture2D Color: register(t0);
sampler ColorSampler: register(s0);



struct PS_INPUT
{
    float4 position: SV_POSITION;
    float2 texcoord: TEXCOORD0;
    float3 normal: NORMAL0;
    float3 direction_to_camera: TEXCOORD1;
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



float4 psmain(PS_INPUT input) : SV_TARGET
{
	return Color.Sample(ColorSampler, 1.0 - input.texcoord);
    float4 color = Color.Sample(ColorSampler, float2(input.texcoord.x, 1.0 - input.texcoord.y));
    
    //AMBIENT LIGHT
    float ka = 8.5;
    float3 ia = float3(0.02, 0.02, 0.02);
    ia *= (color.rbg);
    
    float3 ambient_light = ka * ia;
    
    //DIFFUSE LIGHT
    float kd =0.7;
    float amount_diffuse_light = dot(m_light_direction.xyz, input.normal);
    float3 id = float3(1, 1, 1);
    id *= (color.rbg);
    
    float3 diffuse_light = kd * id * amount_diffuse_light;
    
    //SPECULAR LIGHT
    float ks = 1.0;
    float3 is = float3(1.0, 1.0, 1.0);
    float3 reflected_light = reflect(m_light_direction.xyz, input.normal);
    float shininess = 10.0;
    float amount_specular_light = 0;
    
    amount_specular_light = pow(max(0.0, dot(reflected_light, input.direction_to_camera)), shininess);
    
    float3 specular_light = ks * amount_specular_light * is;
    
    float3 final_light = ambient_light + diffuse_light + specular_light;

    return float4(final_light, 1.0);
}
