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
	#pragma region FORMWORK

	EXTERN API void* CreateRenderWindow(HWND Parent)
	{
		return MakeWindowArg(AsViewport, Parent);
	}
	
	EXTERN API void* CreateRenderWindowBorders()
	{
		return MakeWindow(Classic);
	}

	EXTERN API void* GetRenderWindowHandle(HWIN viewport)
	{
		return ((Window*)viewport)->GetHandler();
	}

	EXTERN API void StopRenderWindow(HWIN viewport)
	{
		((Window*)viewport)->Stop();
	}

	#pragma endregion
	


	#pragma region RENDERWORK

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

	EXTERN API int RunWithGraphics2(HWND Parent, HWND viewport_pointer)
	{
		// Input initialization
		try { InputSystem::Create(); }
		catch (...) { return -1; }

		HWIN window = MakeWindowArg(AsViewport, Parent);
		viewport_pointer = ((Window*)window)->GetHandler();
		HENGINE engine = CreateEngine();
		HVP viewport = CreateViewport(GetWindowHandler(window), engine);

		HDESC hDesc =
		{
			window,		// hWin
			engine,		// hEngine
			viewport	// hViewPort
		};

		Controller control = Controller(&hDesc);
		WindowCallback* callback = new WindowCallback(&hDesc, &control);

		SetWindowCallback(window, (void*)callback);

		// Loop
		callback->OnCreate();
		OnCreateViewport(viewport);
		while (WindowRunning(window))
			InputSystem::Get()->Update();

		// App finish
		InputSystem::Release();
		return 0;
	}

	EXTERN API void CreateGraphics(HWIN windowPtr)
	{
		try { InputSystem::Create(); }
		catch (...) {  }

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
	}

	EXTERN API void UpdateGraphics(HWIN windowPtr)
	{
		if(WindowRunning(windowPtr))
			InputSystem::Get()->Update();
	}

	EXTERN API void DestroyGraphics()
	{
		InputSystem::Release();
	}

	#pragma endregion
}