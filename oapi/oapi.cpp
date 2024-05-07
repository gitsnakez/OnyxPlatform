/// Copyright (C) 2024 Roman Sivkov - All Rights Reserved.
/// You may use, distribute and modify this code under the
/// terms of the MIT License
///
/// Permission is hereby granted, free of charge, to any person obtaining a copy
/// of this software and associated documentation files(the "Software"), to deal
/// in the Software without restriction, including without limitation the rights
/// to use, copy, modify, merge, publish, distribute, sublicense, and /or sell
/// copies of the Software, and to permit persons to whom the Software is
/// furnished to do so, subject to the following conditions :
///
/// The above copyright notice and this permission notice shall be included in all
/// copies or substantial portions of the Software.
///
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
/// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
/// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
/// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
/// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
/// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
/// SOFTWARE.
///
/// For more information contact snakezfortress04@gmail.com
#include <Windows.h>
#include <uxtheme.h>
#include "ErrorDispatcher.h"
#include "steam_api.h"
#include "SteamStartAch.h"
#include "defs.h"
#include "Controller.h"
#include "owm.h"
#include "engine.h"
#include "WindowCallback.h"
#include "SteamStatus.h"
#include "OPlus/OPlus.h"
#include <string>
#include <thread>
#include <combaseapi.h>
#include <shellapi.h>

using namespace std;

namespace onyxengine
{
#pragma region FORMWORK

	EXTERN API void* CreateRenderViewportWindow(HWND Parent)
	{
		return MakeWindowArg(AsViewport, Parent);
	}

	EXTERN API void* CreateRenderWindowBorderless()
	{
		return MakeWindow(Borderless);
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

	EXTERN API void InitGraphics(HWIN windowPtr)
	{
		// Input initialization
		try { InputSystem::Create(); }
		catch (...) { }

		HENGINE engine = CreateEngine();
		HVP viewport = CreateViewport(GetWindowHandler(windowPtr), engine, true);

		HDESC hDesc =
		{
			windowPtr,  //	hWin
			engine,		//	hEngine
			viewport	//	hViewPort
		};

		WindowCallback* callback = new WindowCallback(&hDesc, nullptr);
		SetWindowCallback(windowPtr, (void*)callback);
	}

	EXTERN API void LoopGraphics(HWIN windowPtr)
	{
		// Loop
		while (WindowRunning(windowPtr))
			InputSystem::Get()->Update();
	}

	EXTERN API int DestroyGraphics(HWIN windowPtr)
	{
		InputSystem::Release();
		return 0;
	}

	EXTERN API int RunWithGraphics(HWIN windowPtr)
	{
		// Input initialization
		try { InputSystem::Create(); }
		catch (...) { return 1; }

		HENGINE engine = CreateEngine();
		HVP viewport = CreateViewport(GetWindowHandler(windowPtr), engine, true);

		HDESC hDesc =
		{
			windowPtr,  //	hWin
			engine,		//	hEngine
			viewport	//	hViewPort
		};

		WindowCallback* callback = new WindowCallback(&hDesc, nullptr);
		SetWindowCallback(windowPtr, (void*)callback);

		// Loop
		while (WindowRunning(windowPtr))
			InputSystem::Get()->Update();

		// App finish
		InputSystem::Release();
		return 0;
	}
}

#pragma endregion