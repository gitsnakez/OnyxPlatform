#pragma once
#include "Prerequisites.h"
#include "ErrorDispatcher.h"
#include <SpriteFont.h>

class Font2D
{
public:
	Font2D(const wchar_t* fullpath, RenderSystem* rsystem);
	RECT GetBoundsFromText(const wchar_t* text);

	bool isHaveError = false;

private:
	std::unique_ptr<DirectX::DX11::SpriteFont> _pFont = nullptr;
	std::unique_ptr<DirectX::DX11::SpriteBatch> _pBatch = nullptr;

	RenderSystem *_pRenderSystem = nullptr;

	friend class Font;
};