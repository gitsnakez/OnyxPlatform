// Copyright (c) 2023 snakEZ
// All rights reserved

#include "PixelShader.h"
#include "ExceptHelper.h"

PixelShader::PixelShader(const void* shader_byte_code, size_t byte_code_size, RenderSystem* system): m_system(system)
{
	if (!SUCCEEDED(m_system->m_d3d_device->CreatePixelShader(shader_byte_code, byte_code_size, nullptr, &m_ps)))
	{
		//MessageBox(nullptr, L"DirectX 11:\nPixel shader initialize failure!", L"Engine", MB_ICONSTOP);
		ExceptHelper::ShowError("Creating pixel shader failure!");
	}
}

PixelShader::~PixelShader()
{
	m_ps->Release();
}