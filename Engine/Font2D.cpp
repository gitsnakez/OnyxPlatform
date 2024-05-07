#include "Font2D.h"
#include "RenderSystem.h"

Font2D::Font2D(const wchar_t* fullpath, RenderSystem* rsystem)
{
	_pRenderSystem = rsystem;
	_pFont = std::make_unique<DirectX::DX11::SpriteFont>(_pRenderSystem->m_d3d_device, fullpath);
	if (!_pFont)
		ShowErrorMessage("Font2D initialization failure!");

	auto context = _pRenderSystem->m_imm_context;
	_pBatch = std::make_unique<DirectX::DX11::SpriteBatch>(context);
	if (!_pBatch)
		ShowErrorMessage("Font2D Batch initialization failure!");
}

RECT Font2D::GetBoundsFromText(const wchar_t* text)
{
	try
	{
		auto rc = _pFont->MeasureDrawBounds(text, DirectX::XMFLOAT2(0, 0));
		return rc;
	}
	catch (...)
	{
		isHaveError = true;
		auto rc = _pFont->MeasureDrawBounds(L"error", DirectX::XMFLOAT2(0, 0));
		return rc;
	}
}