#pragma once
#include "Resource.h"
#include "ResourceManager.h"
#include "ErrorDispatcher.h"
#include "Font2D.h"

class Font : public Resource
{
public:
	Font(const wchar_t* path, RenderSystem* rsystem);
	Font2DPtr& GetFont();
	RECT GetBounds(const wchar_t* text);
	void DrawUIString(const wchar_t* text, float x, float y);

private:
	Font2DPtr _pFont;
};

class FontUtility
{
public:
	bool CreateFont(const wchar_t* fontname, float fontsize, const wchar_t* outputpath);
};