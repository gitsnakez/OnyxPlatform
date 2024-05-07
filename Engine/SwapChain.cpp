// Copyright (c) 2023 snakEZ
// All rights reserved

#include "SwapChain.h"
#include "RenderSystem.h"
#include "ErrorDispatcher.h"

SwapChain::SwapChain(HWND hWnd, UINT WinWidth, UINT WinHeight, RenderSystem* system) : m_system(system)
{
    ID3D11Device* device = m_system->m_d3d_device;

    DXGI_SWAP_CHAIN_DESC desc;
    ZeroMemory(&desc, sizeof(desc));
    desc.BufferCount = 1;
    desc.BufferDesc.Width = WinWidth;
    desc.BufferDesc.Height = WinHeight;
    desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    desc.BufferDesc.RefreshRate.Numerator = 60;
    desc.BufferDesc.RefreshRate.Denominator = 1;
    desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    desc.OutputWindow = hWnd;
    desc.SampleDesc.Count = 1;
    desc.SampleDesc.Quality = 0;
    desc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    desc.Windowed = TRUE;

    // Create the swap chain for the window indicated by HWND parameter.
    HRESULT hr = m_system->m_dxgi_factory->CreateSwapChain(device, &desc, &m_swap_chain);

    ReloadBuffers(WinWidth, WinHeight);
}

SwapChain::~SwapChain()
{
    m_rtv->Release();
    m_swap_chain->Release();
}

void SwapChain::Resize(unsigned int width, unsigned int height)
{
    if (m_rtv) m_rtv->Release();
    if (m_dsv) m_dsv->Release();
    
    m_swap_chain->ResizeBuffers(1, width, height, DXGI_FORMAT_R8G8B8A8_UNORM, 0);
    ReloadBuffers(width, height);// ReloadBuffers(width, height);
}

void SwapChain::SetFullsceenMode(bool isfullscr, UINT width, UINT height)
{
    Resize(width, height);
    m_swap_chain->SetFullscreenState(isfullscr, nullptr);
}

bool SwapChain::Present(bool vsync)
{
    m_swap_chain->Present(vsync, NULL);
    return true;
}

void SwapChain::ReloadBuffers(unsigned int width, unsigned int height)
{
    ID3D11Device* device = m_system->m_d3d_device;
    ID3D11Texture2D* buffer = NULL;

    HRESULT hr = m_swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&buffer);

    if (FAILED(hr))
        ShowErrorMessage("Get buffer from swap chain failure!\nSwapChain creation was failed!");

    hr = device->CreateRenderTargetView(buffer, NULL, &m_rtv);
    buffer->Release();

    if (FAILED(hr))
        ShowErrorMessage("Creating render target view failure!\nSwapChain creation was failed!");

    D3D11_TEXTURE2D_DESC tex_desc = {};
    tex_desc.Width = width;
    tex_desc.Height = height;
    tex_desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    tex_desc.Usage = D3D11_USAGE_DEFAULT;
    tex_desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    tex_desc.MipLevels = 1;
    tex_desc.SampleDesc.Count = 1;
    tex_desc.SampleDesc.Quality = 0;
    tex_desc.MiscFlags = 0;
    tex_desc.ArraySize = 1;
    tex_desc.CPUAccessFlags = 0;

    hr = device->CreateTexture2D(&tex_desc, nullptr, &buffer);

    if (FAILED(hr))
        ShowErrorMessage("Creating depth stencil view failure!\nSwapChain creation was failed!");

    hr = device->CreateDepthStencilView(buffer, NULL, &m_dsv);
    buffer->Release();

    if (FAILED(hr))
        ShowErrorMessage("Creating depth stencil view failure!\nSwapChain creation was failed!");
}