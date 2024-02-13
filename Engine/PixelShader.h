// Copyright (c) 2023 snakEZ
// All rights reserved

#pragma once
#include <d3d11.h>
#include "Prerequisites.h"
#include "RenderSystem.h"

class PixelShader
{
public:
	PixelShader(const void* shader_byte_code, size_t byte_code_size, RenderSystem* system);
	~PixelShader();
private:
	ID3D11PixelShader* m_ps;
	RenderSystem* m_system = nullptr;

	friend class RenderSystem;
	friend class DeviceContext;
};