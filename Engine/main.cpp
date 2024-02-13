// Copyright (c) 2023 snakEZ
// All rights reserved

#include "Window.h"
#include "InputSystem.h"
#include "Viewport.h"
#include "api.h"
#include <Dbghelp.h>

#ifdef WINAPP
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	try
	{
		GraphicsEngine::Create();
		InputSystem::Create();
	}
	catch (...) { return -1; }
	{
		try
		{
			Application app;
			while (app.IsRunning());
		}
		catch (...) {
			InputSystem::Release();
			GraphicsEngine::Release();
			return -1;
		}
	}

	InputSystem::Release();
	GraphicsEngine::Release();

	return 0;
}
#elif DLLAPP

EXTERN API void ResizeViewport(Viewport* vp, int width, int heigth)
{
	// LEGACY
	vp->winw = width;
	vp->winh = heigth;
	vp->OnResize();
}

EXTERN API void ReloadMap(Viewport* vp)
{
	vp->LoadMap();
}

EXTERN API void ReloadMaterials(Viewport* vp)
{
	vp->LoadMaterials();
}

EXTERN API void SetVSync(Viewport* vp, bool vsync)
{
	vp->m_vsync = vsync;
}

#pragma region DumpMaker
void make_minidump(EXCEPTION_POINTERS* e)
{
	auto hDbgHelp = LoadLibraryA("dbghelp");
	if (hDbgHelp == nullptr)
		return;
	auto pMiniDumpWriteDump = (decltype(&MiniDumpWriteDump))GetProcAddress(hDbgHelp, "MiniDumpWriteDump");
	if (pMiniDumpWriteDump == nullptr)
		return;

	char name[MAX_PATH];
	{
		auto nameEnd = name + GetModuleFileNameA(GetModuleHandleA(0), name, MAX_PATH);
		SYSTEMTIME t;
		GetSystemTime(&t);
		wsprintfA(nameEnd - strlen(".exe"),
			"_%4d%02d%02d_%02d%02d%02d.dmp",
			t.wYear, t.wMonth, t.wDay, t.wHour, t.wMinute, t.wSecond);
	}

	auto hFile = CreateFileA(name, GENERIC_WRITE, FILE_SHARE_READ, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
	if (hFile == INVALID_HANDLE_VALUE)
		return;

	MINIDUMP_EXCEPTION_INFORMATION exceptionInfo;
	exceptionInfo.ThreadId = GetCurrentThreadId();
	exceptionInfo.ExceptionPointers = e;
	exceptionInfo.ClientPointers = FALSE;

	auto dumped = pMiniDumpWriteDump(
		GetCurrentProcess(),
		GetCurrentProcessId(),
		hFile,
		MINIDUMP_TYPE(MiniDumpWithIndirectlyReferencedMemory | MiniDumpScanMemory),
		e ? &exceptionInfo : nullptr,
		nullptr,
		nullptr);

	CloseHandle(hFile);

	return;
}

LONG CALLBACK unhandled_handler(EXCEPTION_POINTERS* e)
{
	make_minidump(e);
	return EXCEPTION_CONTINUE_SEARCH;
}

EXTERN API void InitializeDumpMaker()
{
	SetUnhandledExceptionFilter(unhandled_handler);
}
#pragma endregion

EXTERN API int CheckDLL()
{
	return 1;
}

#endif