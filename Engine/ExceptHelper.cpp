#include "ExceptHelper.h"
#include <Windows.h>
#include <exception>

void ExceptHelper::ShowError(std::string msg)
{
	std::wstring widestr = std::wstring(msg.begin(), msg.end());

	MessageBox(NULL, widestr.c_str(), L"Engine", MB_OK);
	throw std::exception();
}