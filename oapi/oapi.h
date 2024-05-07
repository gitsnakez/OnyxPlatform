#pragma once

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

#include <Windows.h>
#include "window.h"
#include "defs.h"
#include "api.h"

namespace onyxengine
{
	/// FORMWORK
	EXTERN API void* CreateRenderViewportWindow(HWND Parent);
	EXTERN API void* CreateRenderWindowBorderless();
	EXTERN API void* GetRenderWindowHandle(HWIN viewport);
	EXTERN API void StopRenderWindow(HWIN Wnd);

	// RENDERWORK

	EXTERN API void InitGraphics(HWIN windowPtr);
	EXTERN API void LoopGraphics(HWIN windowPtr);
	EXTERN API int DestroyGraphics(HWIN windowPtr);

	EXTERN API int RunWithGraphics(HWIN windowPtr);
}