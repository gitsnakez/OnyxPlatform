// Copyright (c) 2023 snakEZ
// All rights reserved

#include "api.h"
#include "GraphicsEngine.h"
#include "Font.h"
#include "DeviceContext.h"
#include "ErrorDispatcher.h"

GraphicsEngine* GraphicsEngine::m_engine = nullptr;

EXTERN API GraphicsEngine::GraphicsEngine()
{
    try { m_render_system = new RenderSystem(); }
    catch (...) { ShowErrorMessage("Render system creation failure!"); }

    try { resManager = new ResourceManager(this); }
    catch (...) { ShowErrorMessage("Material manager creation failure!"); }

    void* shader_byte_code = nullptr;
    size_t size_shader = 0;
    m_render_system->CompileVertexShader(L"shaders/vertex_model_layout.shader", "vlsmain", &shader_byte_code, &size_shader);
    ::memcpy(m_mesh_layout_byte_code, shader_byte_code, size_shader);
    m_mesh_layout_size = size_shader;
    m_render_system->ReleaseCompiledShader();
    GraphicsEngine::m_engine = this;
}

EXTERN API GraphicsEngine::~GraphicsEngine()
{
    delete resManager;
    delete m_render_system;
}

EXTERN API RenderSystem* GraphicsEngine::GetRenderSystem()
{
    return m_render_system;
}

EXTERN API ResourceManager* GraphicsEngine::GetResourceManager()
{
    return resManager;
}
/*
ShaderPtr GraphicsEngine::CreateShader(const wchar_t* vertex_shader_path, const wchar_t* pixel_shader_path)
{
    ShaderPtr sdr_ptr = nullptr;

    try
    {
        sdr_ptr = std::make_shared<Shader>(this, vertex_shader_path, pixel_shader_path);
    }
    catch (...) {}
    return sdr_ptr;
}

MaterialPtr GraphicsEngine::CreateMaterial(const ShaderPtr &shader)
{
    MaterialPtr mat_ptr = nullptr;

    try
    {
        mat_ptr = std::make_shared<Material>(shader);
    }
    catch (...) {}
    return mat_ptr;
}

MaterialPtr GraphicsEngine::CreateMaterial(const MaterialPtr& material)
{
    MaterialPtr mat_ptr = nullptr;

    try
    {
        mat_ptr = std::make_shared<Material>(this, material);
    }
    catch (...) {}
    return mat_ptr;
}

ModelPtr GraphicsEngine::CreateModel(const MeshPtr& mesh_ptr, const std::vector<MaterialPtr>& mat_list_ptr)
{
    ModelPtr mdl_ptr = nullptr;

    try
    {
        mdl_ptr = std::make_shared<Model>(mesh_ptr, mat_list_ptr);
    }
    catch (...) {}
    return mdl_ptr;
}
*/
FontPtr GraphicsEngine::CreateUIFont(const wchar_t* path)
{
    FontPtr font_ptr = nullptr;

    try
    {
        font_ptr = std::make_shared<Font>(path, m_render_system);
    }
    catch (...) {}
    return font_ptr;
}

void GraphicsEngine::SetMaterial(const MaterialPtr& material)
{
    GetRenderSystem()->SetRasterizerState(material->m_cull_mode);

    GetRenderSystem()->GetImmediateDeviceContext()->SetConstantBuffer(material->m_vertex_shader, material->m_constant_buffer);
    GetRenderSystem()->GetImmediateDeviceContext()->SetConstantBuffer(material->m_pixel_shader, material->m_constant_buffer);

    //SET DEFAULT SHADER IN THE GRAPHICS PIPELINE TO BE ABLE TO DRAW
    GetRenderSystem()->GetImmediateDeviceContext()->SetVertexShader(material->m_vertex_shader);
    GetRenderSystem()->GetImmediateDeviceContext()->SetPixelShader(material->m_pixel_shader);

    GetRenderSystem()->GetImmediateDeviceContext()->SetTexture(material->m_pixel_shader, &material->m_vec_textures[0], material->m_vec_textures.size());
}

void GraphicsEngine::GetVertexMeshLayoutShaderByteCodeAndSize(void** byte_code, size_t* size)
{
    *byte_code = m_mesh_layout_byte_code;
    *size = m_mesh_layout_size;
}

GraphicsEngine* GraphicsEngine::Get()
{
    return m_engine;
}

EXTERN API void GraphicsEngine::Release()
{
    delete this;
}

EXTERN API void ReleaseEngine(GraphicsEngine* engine)
{
    engine->Release();
}