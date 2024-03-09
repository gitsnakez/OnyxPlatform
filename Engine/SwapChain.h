// Copyright (c) 2023 snakEZ
// All rights reserved

#pragma once
#include <d3d11.h>
#include "Prerequisites.h"

class SwapChain
{
public:
	SwapChain(HWND hWnd, UINT WinWidth, UINT WinHeight, RenderSystem* system);
	~SwapChain();
	void Resize(unsigned int Width, unsigned int Height);
	void SetFullsceenMode(bool isfullscr, UINT width, UINT height);
	bool Present(bool vsync);
private:

	void ReloadBuffers(unsigned int Width, unsigned int Height);

	IDXGISwapChain* m_swap_chain = nullptr;
	ID3D11RenderTargetView* m_rtv = nullptr;
	ID3D11DepthStencilView* m_dsv = nullptr;

	RenderSystem* m_system = nullptr;

	friend class DeviceContext;
};