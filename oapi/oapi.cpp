#include "oapi.h"
#include <Windows.h>
#include "defs.h"
#include "Controller.h"
#include "owm.h"
#include "engine.h"
#include "WindowCallback.h"
#include <string>
#include <thread>

namespace onyxengine
{
	EXTERN API void* CreateViewportWindow(HWND Parent, int Width, int Height)
	{
		return MakeWindowArg(Classic, Parent, Width, Height);
	}

	EXTERN API void* GetViewportHandle(HWIN viewport)
	{
		return ((Window*)viewport)->GetHandler();
	}

	EXTERN API int RunWithGraphics(HWIN windowPtr)
	{
		// Input initialization
		try { InputSystem::Create(); }
		catch (...) { return -1; }

		//HWIN window = MakeWindowArg(Classic);
		HENGINE engine = CreateEngine();
		HVP viewport = CreateViewport(GetWindowHandler(windowPtr), engine);

		HDESC hDesc =
		{
			windowPtr,  // hWin
			engine,		// hEngine
			viewport	// hViewPort
		};

		Controller control = Controller(&hDesc);
		WindowCallback* callback = new WindowCallback(&hDesc, &control);

		SetWindowCallback(windowPtr, (void*)callback);

		// Loop
		callback->OnCreate();
		OnCreateViewport(viewport);
		while (WindowRunning(windowPtr))
			InputSystem::Get()->Update();

		// App finish
		InputSystem::Release();
		return 0;
	}

	EXTERN API void* InitWin32Viewport(HWND Parent, int Width, int Height)
	{
		return InitViewport(Parent, Width, Height);
	}
}