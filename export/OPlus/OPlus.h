#pragma once

#include "api.h"
#include <string>
#include "IConsoleCallback.h"

namespace onyxengine
{
	EXTERN API bool LoadOPlusLibrary();
	EXTERN API void SetIsNewTerminal(bool isNew);
	EXTERN API bool GetIsNewTerminal();
	EXTERN API void ShowError(HWND hmWnd, const char* caption, const char* message, int type, const char* details);

	EXTERN API void SetupCallbacks(IConsoleCallback* callback);
	EXTERN API void SendBuildInfo(const char* compl_time);
	EXTERN API void OpenTerminal();
	EXTERN API void HideTerminal();
}