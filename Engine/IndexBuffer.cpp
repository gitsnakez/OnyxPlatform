// Copyright (c) 2023 snakEZ
// All rights reserved

#include "IndexBuffer.h"
#include "RenderSystem.h"
#include "ErrorDispatcher.h"

IndexBuffer::IndexBuffer(void* list_indices, UINT size_list, RenderSystem* system): m_buffer(0), m_system(system)
{
    D3D11_BUFFER_DESC buff_desc = {};
    buff_desc.Usage = D3D11_USAGE_DEFAULT;
    buff_desc.ByteWidth = 4 * size_list;
    buff_desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    buff_desc.CPUAccessFlags = 0;
    buff_desc.MiscFlags = 0;

    D3D11_SUBRESOURCE_DATA init_data = {};
    init_data.pSysMem = list_indices;

    m_size_list = size_list;

    if (FAILED(m_system->m_d3d_device->CreateBuffer(&buff_desc, &init_data, &m_buffer)))
    {
        //MessageBox(nullptr, L"DirectX 11:\nIndex buffer creation failure!", L"Engine", MB_OK);
        ShowErrorMessage("Creating index buffer failure!");
    }
}

IndexBuffer::~IndexBuffer()
{
    m_buffer->Release();
}

UINT IndexBuffer::GetSizeIndexList()
{
    return this->m_size_list;
}