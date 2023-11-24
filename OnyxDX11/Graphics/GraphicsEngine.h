// Copyright (c) 2023 snakEZ
// All rights reserved

#pragma once
#include <d3d11.h>
#include "ResourceSystem/TextureSystem/TextureManager.h"
#include "RenderSystem/RenderSystem.h"
#include "ResourceSystem/MeshSystem/MeshManager.h"

class GraphicsEngine
{
public:
	GraphicsEngine(); // Initialize the Graphics Engine and DirectX 11 Device.
	~GraphicsEngine();// Release all the resources loaded

	RenderSystem* GetRenderSystem();
	TextureManager* GetMaterialManager();
	MeshManager* GetModelManager();
	void GetVertexMeshLayoutShaderByteCodeAndSize(void** byte_code, size_t* size);

	static GraphicsEngine* Get();

	void Release();

private:
	RenderSystem* m_render_system = nullptr;
	TextureManager* m_mat_manager = nullptr;
	MeshManager* m_mdl_manager = nullptr;
	static GraphicsEngine* m_engine;

	unsigned char m_mesh_layout_byte_code[1024];
	size_t m_mesh_layout_size = 0;
};