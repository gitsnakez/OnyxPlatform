#pragma once

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

#include <windows.h>
#include "defs.h"
#include "api.h"

namespace onyxengine
{
	EXTERN API void* CreateViewportWindow(HWND Parent, int Width, int Height);
	EXTERN API void* GetViewportHandle(HWIN viewport);
	EXTERN API int RunWithGraphics(HWIN windowPtr);
	EXTERN API void* InitWin32Viewport(HWND Parent, int Width, int Height);
}