// Copyright (c) 2023 snakEZ
// All rights reserved

#pragma once

#include <d3d11.h>
#include "Prerequisites.h"

class IndexBuffer
{
public:
	IndexBuffer(void* list_indices, UINT size_list, RenderSystem* system);
	~IndexBuffer();
	UINT GetSizeIndexList();
private:
	UINT m_size_list;
	ID3D11Buffer* m_buffer;
	RenderSystem* m_system = nullptr;
private:
	friend class DeviceContext;
};