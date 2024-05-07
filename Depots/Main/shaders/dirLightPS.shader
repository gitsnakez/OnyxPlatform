Texture2D Color: register(t0);
sampler ColorSampler: register(s0);

Texture2D Normal: register(t1);
sampler NormalSampler: register(s1);



struct PS_INPUT
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



float4 psmain(PS_INPUT input) : SV_TARGET
{
    float4 color = Color.Sample(ColorSampler, float2(input.texcoord.x, 1.0 - input.texcoord.y));
    float4 normal = Normal.Sample(NormalSampler, float2(input.texcoord.x, 1.0 - input.texcoord.y));
    
    normal.xyz = (normal.xyz * 2.0) - 1.0;
    normal.xyz = mul(normal.xyz, input.tbn);
    
    float dot_nl = dot(m_light_direction.xyz, input.tbn[2]);
    
    //AMBIENT LIGHT
    float ka = 0.5;
    float3 ia = float3(1, 1, 1);
    ia *= color.rgb;
    float3 ambient_light = ka * ia;
    
    //DIFFUSE LIGHT
    float kd = 0.5;
    float amount_diffuse_light = dot(m_light_direction.xyz, normal.xyz);
    float3 id = float3(1, 1, 1);
    id *= color.rgb;
    float3 diffuse_light = kd * id * amount_diffuse_light;
    
    //SPECULAR LIGHT
    float ks = 0.1;
    float3 is = float3(1, 1, 1);
    float3 reflected_light = reflect(m_light_direction.xyz, normal.xyz);
    float shininess = 0.1;
    float amount_specular_light = 0;
    if(dot_nl > 0)
        amount_specular_light = pow(max(0.0f, dot(reflected_light, input.direction_to_camera)), shininess);
    float3 specular_light = ks * amount_specular_light * is;
    
	// FINAL LIGHT CALCULATIONS
    float3 final_light = ambient_light + diffuse_light;// + specular_light;
    return float4(final_light, 1.0);
}


//float4 psmain(PS_INPUT input) : SV_TARGET
//{
//    float3 texColor = Color.Sample(ColorSampler, float2(input.texcoord.x, 1.0 - input.texcoord.y)).rgb;
//    float3 normalTex = Normal.Sample(NormalSampler, float2(input.texcoord.x, 1.0 - input.texcoord.y)).rgb * 2.0f - 1.0f;
//    normalTex = normalize(normalTex);
//    float3 normal = normalize(mul(normalTex, input.tbn));
//
//    float3 lightDir = normalize(m_light_position.xyz - input.position.xyz);
//    float3 viewDir = normalize(m_camera_position.xyz - input.position.xyz);
//
//    float3 ambient = texColor * 0.2f; // Пример коэффициента окружающего освещения (ambient)
//
//    float diff = max(0.0f, dot(normal, lightDir));
//    float3 diffuse = texColor * diff; // Пример коэффициента диффузного освещения (diffuse)
//
//    float3 halfway = normalize(lightDir + viewDir);
//    float spec = pow(max(dot(normal, halfway), 0.0f), 32.0f); // Пример коэффициента зеркального блика (specular)
//    float3 specular = spec * float3(0.5f, 0.5f, 0.5f); // Пример цвета зеркального блика
//
//    float3 finalColor = ambient + diffuse + specular;
//
//    return float4(finalColor, 1.0f);
//}