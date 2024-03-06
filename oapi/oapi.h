#pragma once

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

#include <windows.h>
#include "window.h"
#include "defs.h"
#include "api.h"

namespace onyxengine
{
	/// FORMWORK
	EXTERN API void* CreateRenderWindow(HWND Parent);
	EXTERN API void* CreateRenderWindowBorders();
	EXTERN API void* GetRenderWindowHandle(HWIN viewport);
	EXTERN API void StopRenderWindow(HWIN Wnd);

	// RENDERWORK
	EXTERN API int RunWithGraphics(HWIN windowPtr);

	EXTERN API void CreateGraphics(HWIN windowPtr);
	EXTERN API void UpdateGraphics(HWIN windowPtr);
	EXTERN API void DestroyGraphics();
}