// Copyright (c) 2023 snakEZ
// All rights reserved

#include "GraphicsEngine.h"
#include "share.h"
#include "ExceptHelper.h"

GraphicsEngine* GraphicsEngine::m_engine = nullptr;

GraphicsEngine::GraphicsEngine()
{
    try
    {
        m_render_system = new RenderSystem();
    }
    catch (...) { ExceptHelper::ShowError("Render system creation failure!"); }

    try
    {
        m_mat_manager = new TextureManager();
    }
    catch (...) { ExceptHelper::ShowError("Material manager creation failure!"); }

    try
    {
        m_mdl_manager = new MeshManager();
    }
    catch (...) { ExceptHelper::ShowError("Model manager creation failure!"); }

    void* shader_byte_code = nullptr;
    size_t size_shader = 0;
    m_render_system->CompileVertexShader(L"shaders/system_shaders/vertex_model_layout.shader", "vlsmain", &shader_byte_code, &size_shader);
    ::memcpy(m_mesh_layout_byte_code, shader_byte_code, size_shader);
    m_mesh_layout_size = size_shader;
    m_render_system->ReleaseCompiledShader();
    GraphicsEngine::m_engine = this;
}

GraphicsEngine::~GraphicsEngine()
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

void GraphicsEngine::GetVertexMeshLayoutShaderByteCodeAndSize(void** byte_code, size_t* size)
{
    *byte_code = m_mesh_layout_byte_code;
    *size = m_mesh_layout_size;
}

GraphicsEngine* GraphicsEngine::Get()
{
    return m_engine;
}

shared_method void* CreateEngine()
{
    return (void*) new GraphicsEngine();
}

void GraphicsEngine::Release()
{
    delete this;
}

shared_method void ReleaseEngine(GraphicsEngine* engine)
{
    engine->Release();
}