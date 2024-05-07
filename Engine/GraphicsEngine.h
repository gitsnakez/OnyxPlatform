// Copyright (c) 2023 snakEZ
// All rights reserved

#pragma once
#include <d3d11.h>
#include "api.h"
#include "RenderSystem.h"
#include "Material.h"

EXTERN API class GraphicsEngine
{
public:
	API GraphicsEngine(); // Initialize the Graphics Engine and DirectX 11 Device.
	API ~GraphicsEngine();// Release all the resources loaded

	API RenderSystem* GetRenderSystem();
	API ResourceManager* GetResourceManager();
	FontPtr CreateUIFont(const wchar_t* path);
	void SetMaterial(const MaterialPtr& material);
	void GetVertexMeshLayoutShaderByteCodeAndSize(void** byte_code, size_t* size);

	std::atomic<bool> isLevelLoaded = false;
	static GraphicsEngine* Get();

	API void Release();

private:
	RenderSystem* m_render_system = nullptr;
	ResourceManager* resManager = nullptr;
	static GraphicsEngine* m_engine;

	unsigned char m_mesh_layout_byte_code[1024];
	size_t m_mesh_layout_size = 0;
};