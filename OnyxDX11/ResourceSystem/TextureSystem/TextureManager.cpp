#include "TextureManager.h"
#include "Texture.h"

TextureManager::TextureManager(): ResourceManager()
{
}

TextureManager::~TextureManager()
{
}

TexturePtr TextureManager::CreateTextureFormFile(const wchar_t* filename)
{
	return std::static_pointer_cast<Texture>(CreateResourceFromFile(filename));
}

Resource* TextureManager::CreateResourceFromFileConcrete(const wchar_t* filename)
{
	Texture* mat = nullptr;

	try
	{
		mat = new Texture(filename);
	}
	catch (...) {}

	return mat;
}