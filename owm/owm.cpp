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

#include "owm.h"
#include "standart_resources.h"
#include "IWindowCallback.h"
#include "HwndViewport.h"

namespace onyxengine
{
	void* _CrtWnd(INT _preset)
	{
		RECT rc = Window::GetScreenRectangle();

		switch (_preset)
		{
		case GameReady:
		{
			int center_x = (rc.right / 2) - (STANDART_WIDTH_WITH_BORDER / 2);
			int center_y = (rc.bottom / 2) - (STANDART_HEIGHT_WITH_BORDER / 2);
			return (void*) new Window(STANDART_WINDOW_CLASSNAME,
				STANDART_WINDOW_NAME,
				center_x, center_y,
				STANDART_WIDTH_WITH_BORDER,
				STANDART_HEIGHT_WITH_BORDER,
				L"bin\\icon.ico");
		}

		case Classic:
		{
			int center_x = (rc.right / 2) - (STANDART_WIDTH_WITH_BORDER / 2);
			int center_y = (rc.bottom / 2) - (STANDART_HEIGHT_WITH_BORDER / 2);
			return (void*) new Window(STANDART_WINDOW_CLASSNAME,
				STANDART_WINDOW_NAME,
				STANDART_WINDOW_STYLES,
				STANDART_WINDOW_EX_STYLES,
				center_x, center_y,
				STANDART_WIDTH_WITH_BORDER,
				STANDART_HEIGHT_WITH_BORDER,
				L"bin\\icon.ico");
		}

		case NoBorder:
		{
			int center_x = (rc.right / 2) - (STANDART_WIDTH / 2);
			int center_y = (rc.bottom / 2) - (STANDART_HEIGHT / 2);
			return (void*) new Window(STANDART_WINDOW_CLASSNAME, STANDART_WINDOW_NAME,
				GAME_STYLES_NOBORDER, GAME_WINDOW_EX_STYLES,
				center_x, center_y, STANDART_WIDTH, STANDART_HEIGHT, L"");
		}

		default:
		{
			int center_x = (rc.right / 2) - (STANDART_WIDTH_WITH_BORDER / 2);
			int center_y = (rc.bottom / 2) - (STANDART_HEIGHT_WITH_BORDER / 2);
			return (void*) new Window(STANDART_WINDOW_CLASSNAME, STANDART_WINDOW_NAME,
				center_x, center_y, STANDART_WIDTH, STANDART_HEIGHT, L"");
		}
		}
	}

	EXTERN API void* MakeWindow(WinPreset preset)
	{
		return _CrtWnd(preset);
	}

	EXTERN API void* MakeWindowArg(WinPreset preset, HWND Parent, int Width, int Height)
	{
		void* _vpWnd = _CrtWnd(preset);
		HWND _vpHwnd = ((Window*)_vpWnd)->GetHandler();

		RECT rect{};
		GetWindowRect(Parent, &rect);
		AdjustWindowRect(&rect, WS_CHILD, FALSE);

		MoveWindow(_vpHwnd, 0, 0, Width, Height, TRUE);
		ShowWindow(_vpHwnd, SW_SHOWNORMAL);
		UpdateWindow(_vpHwnd);

		return _vpWnd;
	}

	EXTERN API HWND GetWindowHandler(void* window)
	{
		return ((Window*)window)->GetHandler();
	}

	EXTERN API bool WindowRunning(void* window)
	{
		return ((Window*)window)->IsRunning();
	}

	EXTERN API bool SetWindowCallback(void* window, void* callback)
	{
		return ((Window*)window)->callback = (IWindowCallback*)callback;
	}

	EXTERN API void* InitViewport(HWND Parent, int Width, int Height)
	{
		HwndViewport hwndVP = HwndViewport(Parent, Width, Height);
		return hwndVP.GetHandle();
	}
}