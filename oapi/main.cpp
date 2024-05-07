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

// steam appid 2872880

#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

using namespace onyxengine;
using namespace std;

void SetupDllDirectory()
{
	SetDllDirectoryW(L"bin\\");
	SetDllDirectoryA("bin\\");
}

//check tagCOINIT in combaseapi
enum LocalThreadApartmentEnum
{
	MTA_Thread = 0x0,
	STA_Thread = 0x2
};

HRESULT SetThreadApartment(int value)
{
	return CoInitializeEx(NULL, value);
}

///
/// THIS IS MAIN FUNCTION
///
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// Set-up path to dll catalog
	SetupDllDirectory();

	// Single Thread Apartment. Îäíîïîòî÷ííîå ïðèëîæåíèå.
	if(SetThreadApartment(STA_Thread) != S_OK)
		ShowErrorMessage("Problem with thread apartment.", NULLSTR, NULLSTR);

	// Disable windows visual styles
	DWORD dwFlags = (STAP_ALLOW_NONCLIENT);
	SetThemeAppProperties(dwFlags);

	#if _STEAM
	// Check for steam application
	if (SteamAPI_RestartAppIfNecessary(2872880))
	{
		ShowErrorMessage("Game was launch not through Steam.\nPlease restart it through Steam!", NULLSTR, NULLSTR);
		return -1;
	}

	// Steam stuff
	SteamErrMsg msg = {};
	auto result = SteamAPI_InitEx(&msg);

	if (result != k_ESteamAPIInitResult_OK)
	{
		ShowSteamErrorMessage(msg);
		return 1;
	}
	#else
	ShowOnyxMessage("WARNING! This is non-public copy of software.\nIf you are not developer or confidant, please,\ndo not leak information.\n\n\t\t\tOnyx Platform© 2024", "Confidential politics");
	#endif

	// Input initialization
	try { InputSystem::Create(); }
	catch (...) { SteamAPI_Shutdown(); return 1; }

	HWIN window = MakeWindow(Classic);
	((Window*)window)->ShowLogo();
	HENGINE engine = CreateEngine();
	HVP viewport = CreateViewport(GetWindowHandler(window), engine, true);

	HDESC hDesc =
	{
		window,  //	hWin
		engine,	 //	hEngine
		viewport //	hViewPort
	};

	Controller control = Controller(&hDesc);
	WindowCallback* callback = new WindowCallback(&hDesc, &control);

	SetWindowCallback(window, (void*)callback);

	#if _STEAM
	SetSteamStatus("In game", "#onx_ingame");
	SetFirstStartAchievement();
	#endif

	// Loop
	while (WindowRunning(window))
		InputSystem::Get()->Update();

	// App finish
	InputSystem::Release();

	SteamAPI_Shutdown();
	return 0;
}