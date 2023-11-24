// Copyright (c) 2023 snakEZ
// All rights reserved

#include "RenderSystem.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"

#include <d3dcompiler.h>
#include "ExceptHelper.h"

RenderSystem::RenderSystem()
{
    D3D_DRIVER_TYPE driver_types[] =
    {
        D3D_DRIVER_TYPE_HARDWARE,
        D3D_DRIVER_TYPE_WARP,
        D3D_DRIVER_TYPE_REFERENCE
    };

    UINT num_driver_types = ARRAYSIZE(driver_types);

    D3D_FEATURE_LEVEL feauter_levels[] =
    {
        D3D_FEATURE_LEVEL_11_0
    };

    UINT num_feauter_levels = ARRAYSIZE(feauter_levels);

    HRESULT res = 0;

    for (UINT driver_type_index = 0; driver_type_index < num_driver_types;)
    {
        res = D3D11CreateDevice(NULL,
            driver_types[driver_type_index],
            NULL, NULL,
            feauter_levels,
            num_feauter_levels,
            D3D11_SDK_VERSION,
            &m_d3d_device,
            &m_feauter_level,
            &m_imm_context);

        if (SUCCEEDED(res))
        {
            break;
        }
        ++driver_type_index;
    }

    if (FAILED(res))
        ExceptHelper::ShowError("DirectX 11 creation device failure!");

    m_imm_device_context = std::make_shared<DeviceContext>(m_imm_context, this);

    m_d3d_device->QueryInterface(__uuidof(IDXGIDevice), (void**)&m_dxgi_device);
    m_dxgi_device->GetParent(__uuidof(IDXGIAdapter), (void**)&m_dxgi_adapter);
    m_dxgi_adapter->GetParent(__uuidof(IDXGIFactory), (void**)&m_dxgi_factory);

    InitializeRasterizerState();
}

RenderSystem::~RenderSystem()
{
    if (m_vs) m_vs->Release();
    if (m_ps) m_ps->Release();

    if (m_vsblob) m_vsblob->Release();
    if (m_psblob) m_psblob->Release();

    m_dxgi_device->Release();
    m_dxgi_adapter->Release();
    m_dxgi_factory->Release();

    m_d3d_device->Release();
}

bool RenderSystem::CompileVertexShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size)
{
    ID3DBlob* errblob = nullptr;
    if (!SUCCEEDED(D3DCompileFromFile(file_name, nullptr, nullptr, entry_point_name, "vs_5_0", 0, 0, &m_blob, &errblob)))
    {
        MessageBox(nullptr, L"DirectX 11:\nVertex shader compilation failed!", L"Engine", MB_ICONERROR);
        if (errblob)errblob->Release();
        return false;
    }

    *shader_byte_code = m_blob->GetBufferPointer();
    *byte_code_size = m_blob->GetBufferSize();

    return true;
}

bool RenderSystem::CompilePixelShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size)
{
    ID3DBlob* errblob = nullptr;
    if (!SUCCEEDED(D3DCompileFromFile(file_name, nullptr, nullptr, entry_point_name, "ps_5_0", 0, 0, &m_blob, &errblob)))
    {
        MessageBox(nullptr, L"DirectX 11:\nPixel shader compilation failed!", L"Engine", MB_ICONERROR);
        if (errblob)errblob->Release();
        return false;
    }

    *shader_byte_code = m_blob->GetBufferPointer();
    *byte_code_size = m_blob->GetBufferSize();

    return true;
}

void RenderSystem::ReleaseCompiledShader()
{
    if (m_blob)m_blob->Release();
}

void RenderSystem::SetRasterizerState(RaserizerState state)
{
    if (state == Front)
    {
        m_imm_context->RSSetState(m_cull_front_state);
    }
    else
    {
        m_imm_context->RSSetState(m_cull_back_state);
    }
}

SwapChainPtr RenderSystem::CreateSwapChain(HWND hWnd, UINT WinWidth, UINT WinHeight)
{
    SwapChainPtr sc_ptr = nullptr;

    SavedWinWidth = WinWidth;
    SavedWinHeight = WinHeight;

    try
    {
        sc_ptr = std::make_shared<SwapChain>(hWnd, WinWidth, WinHeight, this);
    }
    catch(...){}
    return sc_ptr;
}

DeviceContextPtr RenderSystem::GetImmediateDeviceContext()
{
    return this->m_imm_device_context;
}

VertexBufferPtr RenderSystem::CreateVertexBuffer(void* list_vertices, UINT size_vertex, UINT size_list, void* shader_byte_code, size_t size_byte_shader)
{
    VertexBufferPtr vb_ptr = nullptr;

    try
    {
        vb_ptr = std::make_shared<VertexBuffer>(list_vertices, size_vertex, size_list, shader_byte_code, size_byte_shader, this);
    }
    catch (...) {}
    return vb_ptr;
}

ConstantBufferPtr RenderSystem::CreateConstantBuffer(void* buffer, UINT size_buffer)
{
    ConstantBufferPtr cb_ptr = nullptr;

    try
    {
        cb_ptr = std::make_shared<ConstantBuffer>(buffer, size_buffer, this);
    }
    catch (...) {}
    return cb_ptr;
}

IndexBufferPtr RenderSystem::CreateIndexBuffer(void* list_indices, UINT size_list)
{
    IndexBufferPtr ib_ptr = nullptr;

    try
    {
        ib_ptr = std::make_shared<IndexBuffer>(list_indices, size_list, this);
    }
    catch (...) {}
    return ib_ptr;
}

VertexShaderPtr RenderSystem::CreateVertexShader(const void* shader_byte_code, size_t byte_code_size)
{
    VertexShaderPtr vs_ptr = nullptr;

    try
    {
        vs_ptr = std::make_shared<VertexShader>(shader_byte_code, byte_code_size, this);
    }
    catch (...) {}
    return vs_ptr;
}

PixelShaderPtr RenderSystem::CreatePixelShader(const void* shader_byte_code, size_t byte_code_size)
{
    PixelShaderPtr ps_ptr = nullptr;

    try
    {
        ps_ptr = std::make_shared<PixelShader>(shader_byte_code, byte_code_size, this);
    }
    catch (...) {}
    return ps_ptr;
}

void RenderSystem::InitializeRasterizerState()
{
    D3D11_RASTERIZER_DESC desc = {};

    desc.DepthClipEnable = true;
    desc.FillMode = D3D11_FILL_SOLID;

    // Front init
    desc.CullMode = D3D11_CULL_FRONT;
    m_d3d_device->CreateRasterizerState(&desc, &m_cull_front_state);

    // Back init
    desc.CullMode = D3D11_CULL_BACK;
    m_d3d_device->CreateRasterizerState(&desc, &m_cull_back_state);
}