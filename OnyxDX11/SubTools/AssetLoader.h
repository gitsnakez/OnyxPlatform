#pragma once

#include "ResourceSystem/TextureSystem/Texture.h"
#include "ResourceSystem/MeshSystem/Mesh.h"
#include "RenderSystem/Prerequisites.h"
#include "Graphics/GraphicsEngine.h"
#include "SubTools/file_reader.h"
#include <map>

class AssetLoader
{
public:
	AssetLoader();
	~AssetLoader();

	void Release();

	void LoadMaterials(const wchar_t* cfg_filename);
	void LoadModels(const wchar_t* cfg_filename);
	void LoadVertexBuffers(const wchar_t* cfg_filename);
	void LoadPixelShader(const wchar_t* cfg_filename);

	static AssetLoader* Get();

	TexturePtr GetMaterial(std::string filename);
	MeshPtr GetModel(std::string filename);
	VertexBufferPtr GetVertexShader(std::string filename);
	PixelShaderPtr GetPixelShader(std::string filename);

	static AssetLoader* _AssetLoaderPtr;

private:
	std::map<std::string, TexturePtr> m_materials;
	std::map<std::string, MeshPtr> m_models;
	std::map<std::string, VertexBufferPtr> m_vbs;
	std::map<std::string, PixelShaderPtr> m_vps;
};