#pragma once
#include "ResourceManager.h"

class TextureManager: public ResourceManager
{
public:
	TextureManager();
	~TextureManager();
	TexturePtr CreateTextureFormFile(const wchar_t* filename);

protected:
	virtual Resource* CreateResourceFromFileConcrete(const wchar_t* filename);
};