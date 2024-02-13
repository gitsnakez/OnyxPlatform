// Copyright (c) 2023 snakEZ
// All rights reserved

#pragma once
#include <d3d11.h>
#include "Prerequisites.h"
#include "PixelShader.h"
#include "VertexShader.h"
#include "ConstantBuffer.h"

class DeviceContext
{
public:
	DeviceContext(ID3D11DeviceContext* device_context, RenderSystem* system);
	~DeviceContext();

	void ClearRenderTargetColor(const SwapChainPtr& swap_chain, float Red, float Green, float Blue, float Alpha);
	void SetVertexBuffer(const VertexBufferPtr& vertex_buffer);
	void SetIndexBuffer(const IndexBufferPtr& index_buffer);

	void DrawTriangleList(UINT vertex_count, UINT start_vertex_index);
	void DrawIndexedTriangleList(UINT index_count, UINT start_vertex_index, UINT start_index_location);
	void DrawTriangleStrip(UINT vertex_count, UINT start_vertex_index);
	void SetViewportSize(UINT width, UINT height);

	void SetVertexShader(const VertexShaderPtr& vertex_shader);
	void SetPixelShader(const PixelShaderPtr& pixel_shader);

	void SetTexture(const VertexShaderPtr& vertex_shader, const TexturePtr* texture, UINT num_textures);
	void SetTexture(const PixelShaderPtr& pixel_shader, const TexturePtr* texture, UINT num_textures);

	void SetConstantBuffer(const VertexShaderPtr& vertex_shader, const ConstantBufferPtr& buffer);
	void SetConstantBuffer(const PixelShaderPtr& pixel_shader, const ConstantBufferPtr& buffer);
private:
	ID3D11DeviceContext* m_device_context;
	RenderSystem* m_system = nullptr;

	friend class ConstantBuffer;
};