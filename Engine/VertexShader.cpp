// Copyright (c) 2023 snakEZ
// All rights reserved

#include "VertexShader.h"
#include "RenderSystem.h"
#include "ErrorDispatcher.h"

VertexShader::VertexShader(const void* shader_byte_code, size_t byte_code_size, RenderSystem* system): m_system(system)
{
	if (!SUCCEEDED(m_system->m_d3d_device->CreateVertexShader(shader_byte_code, byte_code_size, nullptr, &m_vs)))
	{
		//MessageBox(nullptr, L"DirectX 11:\nVertex shader initialize failure!", L"Engine", MB_ICONSTOP);
		ShowErrorMessage("Creating vertex shader failure!");
	}
}

VertexShader::~VertexShader()
{
	m_vs->Release();
}