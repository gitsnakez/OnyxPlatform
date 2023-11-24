// Copyright (c) 2023 snakEZ
// All rights reserved

#pragma once
#include <d3d11.h>
#include "Prerequisites.h"

enum RaserizerState
{
	Front,
	Back
};

class RenderSystem
{
public:
	RenderSystem();	// Initialize the Graphics Engine and DirectX 11 Device.
	~RenderSystem();// Release all the resources loaded

	bool CompileVertexShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size);
	bool CompilePixelShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size);
	void ReleaseCompiledShader();
	void SetRasterizerState(RaserizerState state);

	SwapChainPtr CreateSwapChain(HWND hWnd, UINT WinWidth, UINT WinHeight);
	DeviceContextPtr GetImmediateDeviceContext();
	VertexBufferPtr CreateVertexBuffer(void* list_vertices, UINT size_vertex, UINT size_list, void* shader_byte_code, size_t size_byte_shader);
	ConstantBufferPtr CreateConstantBuffer(void* buffer, UINT size_buffer);
	IndexBufferPtr CreateIndexBuffer(void* list_indices, UINT size_list);
	VertexShaderPtr CreateVertexShader(const void* shader_byte_code, size_t byte_code_size);
	PixelShaderPtr CreatePixelShader(const void* shader_byte_code, size_t byte_code_size);

private:
	void InitializeRasterizerState();

	DeviceContextPtr m_imm_device_context;

	UINT SavedWinWidth;
	UINT SavedWinHeight;

	ID3D11Device* m_d3d_device;
	D3D_FEATURE_LEVEL m_feauter_level;

	IDXGIDevice* m_dxgi_device;
	IDXGIAdapter* m_dxgi_adapter;
	IDXGIFactory* m_dxgi_factory;
	ID3D11DeviceContext* m_imm_context;

	ID3DBlob* m_blob = nullptr;

	ID3D11RasterizerState* m_cull_front_state = nullptr;
	ID3D11RasterizerState* m_cull_back_state = nullptr;

	ID3DBlob* m_vsblob = nullptr;
	ID3DBlob* m_psblob = nullptr;
	ID3D11VertexShader* m_vs = nullptr;
	ID3D11PixelShader* m_ps = nullptr;
	RenderSystem* m_system = nullptr;

	friend class SwapChain;
	friend class VertexBuffer;
	friend class ConstantBuffer;
	friend class IndexBuffer;
	friend class VertexShader;
	friend class PixelShader;
	friend class Texture;
};