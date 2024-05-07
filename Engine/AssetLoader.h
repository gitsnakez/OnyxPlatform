#pragma once

#include "Texture.h"
#include "Mesh.h"
#include "Prerequisites.h"
#include "GraphicsEngine.h"
#include "file_reader.h"
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
	TexturePtr GetMaterial(std::wstring filename);
	MeshPtr GetModel(std::wstring filename);
	VertexBufferPtr GetVertexShader(std::string filename);
	PixelShaderPtr GetPixelShader(std::string filename);

	static AssetLoader* _AssetLoaderPtr;

private:
	std::map<std::string, TexturePtr> m_materials;
	std::map<std::string, MeshPtr> m_models;
	std::map<std::wstring, TexturePtr> m_w_materials;
	std::map<std::wstring, MeshPtr> m_w_models;
	std::map<std::string, VertexBufferPtr> m_vbs;
	std::map<std::string, PixelShaderPtr> m_vps;
};