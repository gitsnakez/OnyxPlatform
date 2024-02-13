// Copyright (c) 2023 snakEZ
// All rights reserved

#include "GraphicsEngine.h"
#include "api.h"
#include "DeviceContext.h"
#include "ExceptHelper.h"

GraphicsEngine* GraphicsEngine::m_engine = nullptr;

EXTERN API GraphicsEngine::GraphicsEngine()
{
    try { m_render_system = new RenderSystem(); }
    catch (...) { ExceptHelper::ShowError("Render system creation failure!"); }

    try { m_mat_manager = new TextureManager(); }
    catch (...) { ExceptHelper::ShowError("Material manager creation failure!"); }

    try { m_mdl_manager = new MeshManager(); }
    catch (...) { ExceptHelper::ShowError("Model manager creation failure!"); }

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
    delete m_mdl_manager;
    delete m_mat_manager;
    delete m_render_system;
}

RenderSystem* GraphicsEngine::GetRenderSystem()
{
    return m_render_system;
}

TextureManager* GraphicsEngine::GetMaterialManager()
{
    return m_mat_manager;
}

MeshManager* GraphicsEngine::GetModelManager()
{
    return m_mdl_manager;
}

MaterialPtr GraphicsEngine::CreateMaterial(const wchar_t* vertex_shader_path, const wchar_t* pixel_shader_path)
{
    MaterialPtr mat_ptr = nullptr;

    try
    {
        mat_ptr = std::make_shared<Material>(this, vertex_shader_path, pixel_shader_path);
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