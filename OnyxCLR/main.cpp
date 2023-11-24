#include "Window.h"
#include <Windows.h>
#include "external.h"

using namespace System;

#ifdef _WINDLL

	EXTERNAL void* CreateWin()
	{
		return (void*) new Window();
	}

#else

	[STAThreadAttribute]
	int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
	{
		try
		{
			InputSystem::Create();
		}
		catch (...)
		{
			OnyxAPIWrapper::ShowMessage("Engine", "Input system error!");
			return -1;
		}
		RECT rc = Window::GetScreenRectangle();

		int center_x = (rc.right / 2) - ((STANDART_WIDTH_WITH_BORDER) / 2);
		int center_y = (rc.bottom / 2) - ((STANDART_HEIGHT_WITH_BORDER) / 2);

		Window window = Window(STANDART_WINDOW_CLASSNAME, STANDART_WINDOW_NAME, STANDART_CAPTION, true, center_x, center_y, STANDART_WIDTH_WITH_BORDER, STANDART_HEIGHT_WITH_BORDER, L"bin\\icon.ico");
		//Window window;
		while (window.IsRunning())
			InputSystem::Get()->Update();

		InputSystem::Release();
		return 0;
	}

#endif