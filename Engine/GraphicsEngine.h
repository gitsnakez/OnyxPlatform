// Copyright (c) 2023 snakEZ
// All rights reserved

#pragma once
#include <d3d11.h>
#include "api.h"
#include "TextureManager.h"
#include "RenderSystem.h"
#include "MeshManager.h"
#include "Material.h"

EXTERN API class GraphicsEngine
{
public:
	API GraphicsEngine(); // Initialize the Graphics Engine and DirectX 11 Device.
	API ~GraphicsEngine();// Release all the resources loaded

	RenderSystem* GetRenderSystem();
	TextureManager* GetMaterialManager();
	MeshManager* GetModelManager();
	MaterialPtr CreateMaterial(const wchar_t* vertex_shader_path, const wchar_t* pixel_shader_path);
	MaterialPtr CreateMaterial(const MaterialPtr& material);
	void SetMaterial(const MaterialPtr& material);
	void GetVertexMeshLayoutShaderByteCodeAndSize(void** byte_code, size_t* size);

	static GraphicsEngine* Get();

	API void Release();

private:
	RenderSystem* m_render_system = nullptr;
	TextureManager* m_mat_manager = nullptr;
	MeshManager* m_mdl_manager = nullptr;
	static GraphicsEngine* m_engine;

	unsigned char m_mesh_layout_byte_code[1024];
	size_t m_mesh_layout_size = 0;
};