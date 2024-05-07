#include "Font.h"
#include <string>
#include <sstream>
#include <regex>
#include <filesystem>

Font::Font(const wchar_t* path, RenderSystem* rsystem) : Resource(path, rsystem)
{
	_pFont = rsystem->Create2DFont(path);
}

Font2DPtr& Font::GetFont()
{
	return _pFont;
}

RECT Font::GetBounds(const wchar_t* text)
{
	return _pFont->GetBoundsFromText(text);
}

void Font::DrawUIString(const wchar_t* text, float x, float y)
{
	if (_pFont->isHaveError)
	{
		_pFont->_pBatch->Begin();
		_pFont->_pFont->DrawString(_pFont->_pBatch.get(), L"error", DirectX::XMFLOAT2(x, y));
		_pFont->_pBatch->End();
	}
	else
	{
		_pFont->_pBatch->Begin();
		_pFont->_pFont->DrawString(_pFont->_pBatch.get(), text, DirectX::XMFLOAT2(x, y));
		_pFont->_pBatch->End();
	}
}

bool FontUtility::CreateFont(const wchar_t* fontname, float fontsize, const wchar_t* outputpath)
{
	std::wostringstream p;
	std::wstring s = std::regex_replace(fontname, std::wregex(L"\\s+"), L"");

	p << outputpath << s << ".font";

	if (!std::filesystem::exists(p.str()))
	{
		std::wstringstream command;
		command << "bin\\MakeSpriteFont.exe ";
		command << "\"" << fontname << "\" ";
		command << p.str() << " ";
		command << "/FontSize:" << fontsize;
		command << "/Sharp";

		if (_wsystem(command.str().c_str()) != 0)
			ShowErrorMessage("Font creation failure!");

		return true;
	}

	return false;
}
