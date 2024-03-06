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
#include "steam_api.h"
#include "SteamStartAch.h"
#include "defs.h"
#include "Controller.h"
#include "owm.h"
#include "engine.h"
#include "WindowCallback.h"
#include "appMain.h"
#include <string>
#include <thread>

// steam appid 2872880

using namespace onyxengine;
using namespace std;



///
/// THIS IS MAIN FUNCTION
///
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// Steam stuff
	if (!SteamAPI_Init())
	{
		MessageBox(NULL, L"Steam not initialized!", L"Onyx Platform", MB_OK);
		return 0;
	}
	//SteamAPI_RestartAppIfNecessary(2872880);

	// Input initialization
	try { InputSystem::Create(); }
	catch (...) { EngineShutdown(-1); }

	HWIN window = MakeWindow(Classic);
	HENGINE engine = CreateEngine();
	HVP viewport = CreateViewport(GetWindowHandler(window), engine);

	HDESC hDesc =
	{
		window,  //	hWin
		engine,	 //	hEngine
		viewport //	hViewPort
	};

	Controller control = Controller(&hDesc);
	WindowCallback* callback = new WindowCallback(&hDesc, &control);

	SetWindowCallback(window, (void*)callback);
	SetFirstStartAchievement();

	// Loop
	callback->OnCreate();
	OnCreateViewport(viewport);
	while (WindowRunning(window))
		InputSystem::Get()->Update();

	// App finish
	InputSystem::Release();

	EngineShutdown(0);
}