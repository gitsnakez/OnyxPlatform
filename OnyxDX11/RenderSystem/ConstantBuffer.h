// Copyright (c) 2023 snakEZ
// All rights reserved

#pragma once
#include <d3d11.h>
#include "Prerequisites.h"
#include "DeviceContext.h"

class ConstantBuffer
{
public:
	ConstantBuffer(void* buffer, UINT size_buffer, RenderSystem * system);
	~ConstantBuffer();

	void Update(DeviceContextPtr context, void* buffer);

private:
	ID3D11Buffer* m_buffer;
	RenderSystem* m_system = nullptr;

	friend class DeviceContext;
};