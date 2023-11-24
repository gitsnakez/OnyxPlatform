#include "AssetLoader.h"
#include "RenderSystem/Prerequisites.h"

AssetLoader* AssetLoader::_AssetLoaderPtr = nullptr;

AssetLoader::AssetLoader()
{
	AssetLoader::_AssetLoaderPtr = this;
}

AssetLoader::~AssetLoader()
{
}

void AssetLoader::Release()
{
	delete this;
}

void AssetLoader::LoadMaterials(const wchar_t* cfg_filename)
{
	file_reader freader;
	std::map<std::string, std::string> rawmats = freader.GetHeaderDictionaryFromFile(cfg_filename);

	for (const auto& mat : rawmats)
	{
		std::wstring widestr = std::wstring(mat.second.begin(), mat.second.end());
		m_materials[mat.first] = GraphicsEngine::Get()->GetMaterialManager()->CreateTextureFormFile(widestr.c_str());
	}
}

void AssetLoader::LoadModels(const wchar_t* cfg_filename)
{
	file_reader freader;
	std::map<std::string, std::string> rawmdls = freader.GetHeaderDictionaryFromFile(cfg_filename);

	for (const auto& mdl : rawmdls)
	{
		std::wstring widestr = std::wstring(mdl.second.begin(), mdl.second.end());
		m_models[mdl.first] = GraphicsEngine::Get()->GetModelManager()->CreateMeshFormFile(widestr.c_str());
	}
}

void AssetLoader::LoadVertexBuffers(const wchar_t* cfg_filename)
{
}

void AssetLoader::LoadPixelShader(const wchar_t* cfg_filename)
{
}

AssetLoader* AssetLoader::Get()
{
	return _AssetLoaderPtr;
}

TexturePtr AssetLoader::GetMaterial(std::string filename)
{
	return m_materials[filename];
}

MeshPtr AssetLoader::GetModel(std::string filename)
{
	return m_models[filename];
}

VertexBufferPtr AssetLoader::GetVertexShader(std::string filename)
{
	return VertexBufferPtr();
}

PixelShaderPtr AssetLoader::GetPixelShader(std::string filename)
{
	return PixelShaderPtr();
}
