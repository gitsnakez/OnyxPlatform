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

#include "Window.h"
#include <Dwmapi.h>
#include <Uxtheme.h>
#include "oexsys.h"
#include "InputListener.h"
#include "ConvertChars.h"
#include <chrono>
#include <thread>

namespace onyxengine
{
	LRESULT CALLBACK WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
	{
		Window* window;
		switch (Msg)
		{
		case WM_SYSCOMMAND:
			switch (wParam)
			{
			case KEYBOARD:
				break;
			default:
				return ::DefWindowProc(hWnd, Msg, wParam, lParam);
			}
		case WM_COMMAND:
			switch (wParam)
			{
			case 0:
				DestroyWindow(hWnd);
				break;
			}
			break;

		case WM_CREATE:
			window = (Window*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
			if (window) window->OnCreateWindow();
			break;

		case WM_CLOSE:
			window = (Window*)GetWindowLongPtr(hWnd, GWLP_USERDATA);

			if (window)
			{
				bool iscncl = false;
				window->OnClosingWindow(&iscncl);
				if (!iscncl) DestroyWindow(hWnd);
			}
			break;

		case WM_MOVE:
			window = (Window*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
			if (window)
			{
				//Loc								Horizontal(X)				Vertical(Y)
				window->Location = new Point((int)(short)LOWORD(lParam), (int)(short)HIWORD(lParam));

				window->OnChangeWindowPosition(Point((int)(short)LOWORD(lParam), (int)(short)HIWORD(lParam)));
			}
			break;

		case WM_SETFOCUS:
			// Event fired when the window is focused.
			window = (Window*)GetWindowLongPtr(hWnd, GWLP_USERDATA);

			if (window)
				window->OnEnter();

			break;

		case WM_KILLFOCUS:
			// Event fired when the window lost focus.
			window = (Window*)GetWindowLongPtr(hWnd, GWLP_USERDATA);

			if (window)
				window->OnLeave();

			break;

		case WM_DESTROY:
			// Event fired when the window is destroyed.
			window = (Window*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
			//THIS SNIPPET OF CODE WILL RECOVER THE POINTER "THIS" FROM THE SPECIAL STRUCTURE DATA IDENTIFIED BY HWND

			if (window) window->OnDestroyWindow();
			break;

		case WM_SIZE:
			// Event fired when the window resized.
			window = (Window*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
			if (window)
			{
				//Size						Horizontal(x)			Verticla(Y)
				window->Size = new Rectangle((UINT)LOWORD(lParam), (UINT)HIWORD(lParam));
				window->OnResizeWindow(Rectangle((UINT)LOWORD(lParam), (UINT)HIWORD(lParam)));
			}
			break;
			
		default:
			return ::DefWindowProc(hWnd, Msg, wParam, lParam);
		}

		return NULL;
	}

	void Window::Exit()
	{
		Running = false;
	}

	void Window::CreateViewportWindow(HWND Parent)
	{
		WNDCLASSEX wc;
		ZeroMemory(&wc, sizeof(wc));

		wc.cbSize = sizeof(wc);
		wc.style = CS_HREDRAW | CS_VREDRAW;
		wc.lpfnWndProc = &WndProc;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = 0;
		wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground = STANDART_BACKCOLOR;
		wc.lpszMenuName = NULL;
		wc.lpszClassName = STANDART_WINDOW_CLASSNAME;
		wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

		if (!RegisterClassEx(&wc)) // If registration of class will fail, the function will return false
			OExSys::ShowException("Window class failed!", "Onyx engine");

		RECT rect{};
		const wchar_t* caption{ L"onyxengine" };

		GetWindowRect(Parent, &rect);
		AdjustWindowRect(&rect, WS_CHILD, FALSE);

		const int top { rect.top };
		const int left { rect.left };
		const int width { rect.right - left };
		const int height { rect.bottom - top };

		Handle = CreateWindowEx(0, wc.lpszClassName, caption, WS_CHILD, left, top, width, height, Parent, NULL, NULL, NULL);

		if (!Handle) OExSys::ShowException("Window handler failed!", "Onyx engine");

		ShowWindow(Handle, SW_SHOWNORMAL);
		UpdateWindow(Handle);

		// Runnging flag status
		Running = true;
	}

	void Window::CreateWindowForm(
		wstring class_name, wstring text,
		UINT x, UINT y, UINT width,
		UINT height, HBRUSH backcolor,
		HICON icon, DWORD window_styles,
		DWORD window_ex_styles, int dwmdesc[], int showMode)
	{
		// init info
		LPCWSTR win_classname = class_name.c_str();
		LPCWSTR win_title = text.c_str();

		std::string converted_caption = ConvertWstrToStr(text.c_str());

		// creating
		WNDCLASSEX wc;
		wc.cbClsExtra = NULL;
		wc.cbSize = sizeof(WNDCLASSEX);
		wc.cbWndExtra = NULL;
		wc.hbrBackground = backcolor;
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.hIcon = icon;
		wc.hIconSm = icon;
		wc.hInstance = NULL;
		wc.lpszClassName = win_classname;
		wc.lpszMenuName = L"";
		wc.style = NULL;
		wc.lpfnWndProc = &WndProc;

		Location = new Point(x, y);
		Size = new Rectangle(width, height);

		if (!::RegisterClassEx(&wc)) // If registration of class will fail, the function will return false
		{
			OExSys::ShowException("Window class failed!", converted_caption);
		}

		// Creation of the window
		Handle = CreateWindowEx(window_ex_styles, win_classname, win_title, window_styles, x, y, width, height, NULL, NULL, NULL, NULL);

		// If creation of the window fail, return false
		if (!Handle)
		{
			OExSys::ShowException("Window handler failed!", converted_caption);
		}

		//Hard set classic mode
		//SetWindowTheme(Handle, NULL, L"CLASSIC"); int rectCorner = 1;
		//DwmSetWindowAttribute(Handle, DWMWA_WINDOW_CORNER_PREFERENCE, &rectCorner, sizeof(int));
		
		// Set title dark mode
		if (DwmSetWindowAttribute(Handle, 19, &dwmdesc[1], sizeof(int)) != 0)
			DwmSetWindowAttribute(Handle, 20, &dwmdesc[1], sizeof(int));
		
		DwmSetWindowAttribute(Handle, DWMWA_WINDOW_CORNER_PREFERENCE, &dwmdesc[0], sizeof(int));
		DwmSetWindowAttribute(Handle, DWMWA_BORDER_COLOR, &dwmdesc[2], sizeof(COLORREF));
		DwmSetWindowAttribute(Handle, DWMWA_CAPTION_COLOR, &dwmdesc[3], sizeof(COLORREF));
		DwmSetWindowAttribute(Handle, DWMWA_TEXT_COLOR, &dwmdesc[4], sizeof(COLORREF));

		// Show up window
		ShowWindow(Handle, showMode);
		UpdateWindow(Handle);

		// Runnging flag status
		Running = true;
	}



	Window::Window()
	{
		RECT rc = GetScreenRectangle();

		int center_x = (rc.right / 2) - ((STANDART_WIDTH_WITH_BORDER) / 2);
		int center_y = (rc.bottom / 2) - ((STANDART_HEIGHT_WITH_BORDER) / 2);

		int dwmdesc[] = STANDART_DWMDESC;

		CreateWindowForm(
			STANDART_WINDOW_CLASSNAME,
			STANDART_WINDOW_NAME,
			center_x,
			center_y,
			STANDART_WIDTH_WITH_BORDER,
			STANDART_HEIGHT_WITH_BORDER,
			STANDART_BACKCOLOR,
			STANDART_ICON,
			GAME_WINDOW_STYLES,
			GAME_WINDOW_EX_STYLES,
			dwmdesc, SW_SHOW);
	}

	Window::Window(HWND Parent)
	{
		CreateViewportWindow(Parent);
	}

	Window::Window(wstring window_classname, wstring window_title, UINT x, UINT y, UINT width, UINT height, wstring icon_path, INT showMode)
	{
		int dwmdesc[] = STANDART_DWMDESC;
		HICON icon = (icon_path.length() == 0) ? STANDART_ICON : LOAD_FILE_ICON(icon_path.c_str());

		CreateWindowForm(
			window_classname,
			window_title,
			x,
			y,
			width,
			height,
			STANDART_BACKCOLOR,
			icon,
			GAME_WINDOW_STYLES,
			GAME_WINDOW_EX_STYLES,
			dwmdesc, showMode);
	}

	Window::Window(wstring window_classname, wstring window_title, DWORD winStyles, DWORD winExStyles, UINT x, UINT y, UINT width, UINT height, wstring icon_path, INT showMode)
	{
		int dwmdesc[] = STANDART_DWMDESC;
		HICON icon = (icon_path.length() == 0) ? STANDART_ICON : LOAD_FILE_ICON(icon_path.c_str());

		CreateWindowForm(
			window_classname,
			window_title,
			x,
			y,
			width,
			height,
			STANDART_BACKCOLOR,
			icon,
			winStyles,
			winExStyles,
			dwmdesc, showMode);
	}

	Window::Window(wstring window_classname, wstring window_title, DWORD winStyles, DWORD winExStyles, UINT x, UINT y, UINT width, UINT height, wstring icon_path, bool isRectangle, INT showMode)
	{
		int dwmdesc[] = STANDART_DWMDESC;
		dwmdesc[0] = isRectangle ? DWM_DONOTROUND : DWM_ROUND;
		HICON icon = (icon_path.length() == 0) ? STANDART_ICON : LOAD_FILE_ICON(icon_path.c_str());

		CreateWindowForm(
			window_classname,
			window_title,
			x,
			y,
			width,
			height,
			STANDART_BACKCOLOR,
			icon,
			winStyles,
			winExStyles,
			dwmdesc, showMode);
	}

	Window::~Window()
	{/*
		if (!::DestroyWindow(Handle))
		{
			throw std::exception("Destroy window failure!");
		}*/
	}

	bool Window::Broadcast()
	{
		MSG msg;
		if (!this->Initialized)
		{
			SetWindowLongPtr(Handle, GWLP_USERDATA, (LONG_PTR)this);
			this->OnCreateWindow();
			this->Initialized = true;
		}

		this->OnUpdateWindow();

		while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		return true;
	}

	HWND Window::GetHandler()
	{
		return Handle;
	}

	bool Window::IsRunning()
	{
		if (Running)
			Broadcast();

		return Running;
	}

	void Window::ShowLogo(std::wstring banner_filename, int width, int height)
	{
		// Background
		HDC hdc = GetDC(Handle);
		RECT rect = { 0, 0, Size->Width - 16, Size->Height - 39 };
		HBRUSH brush = CreateSolidBrush(RGB(40, 40, 40));
		FillRect(hdc, &rect, brush);

		// Logo
		int x = Size->Width / 2 - width / 2 - 16;
		int y = Size->Height / 2 - height / 2 -39;
		BITMAP bitmap;
		HBITMAP hBitmap = NULL;
		HDC hdcMem;
		HDC oldBitmap;

		hdcMem = CreateCompatibleDC(GetDC(NULL));
		oldBitmap = (HDC)SelectObject(hdcMem, hBitmap);


		hBitmap = (HBITMAP)LoadImage(GetModuleHandle(NULL), banner_filename.c_str(), IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
		oldBitmap = (HDC)SelectObject(hdcMem, hBitmap);
		GetObject(hBitmap, sizeof(bitmap), &bitmap);
		BitBlt(hdc, x, y, bitmap.bmWidth, bitmap.bmHeight, hdcMem, 0, 0, SRCCOPY);

		// Release resources
		SelectObject(hdcMem, oldBitmap);
		DeleteDC(hdcMem);
		DeleteObject(brush);
		ReleaseDC(Handle, hdc);
	}

	void Window::Stop()
	{
		Running = false;
	}

	// Функция для мерцания значка в таскбаре
	void Window::FlashTaskbarIcon(bool flash)
	{
		FLASHWINFO flashInfo;
		flashInfo.cbSize = sizeof(FLASHWINFO);
		flashInfo.hwnd = Handle;
		flashInfo.dwFlags = FLASHW_TRAY | (flash ? FLASHW_ALL : FLASHW_STOP);
		flashInfo.uCount = 15; // Количество мерцаний (можно изменить по желанию)
		flashInfo.dwTimeout = 0;

		FlashWindowEx(&flashInfo);
	}

	RECT Window::GetClientWindowRectangle()
	{
		RECT rc;
		::GetClientRect(Handle, &rc);
		return rc;
	}

	RECT Window::GetWindowRectangle()
	{
		RECT rc;
		::GetWindowRect(Handle, &rc);
		return rc;
	}

	RECT Window::GetScreenRectangle()
	{
		RECT rc;

		rc.left = 0;
		rc.right = GetSystemMetrics(SM_CXSCREEN);
		rc.top = 0;
		rc.bottom = GetSystemMetrics(SM_CYSCREEN);

		return rc;
	}

	void Window::OnCreateWindow()
	{
		isFocused = true;
		InputSystem::Get()->AddListener(this);
		callback->OnCreate();
	}

	void Window::OnUpdateWindow()
	{
		callback->OnUpdate();
	}

	void Window::OnResizeWindow(const Rectangle& size)
	{
		callback->OnResize(size);
	}

	void Window::OnChangeWindowPosition(const Point& location)
	{
		callback->OnChangePosition(location);
	}

	void Window::OnClosingWindow(bool* isCancle)
	{
		callback->OnClosing(isCancle);
	}

	void Window::OnDestroyWindow()
	{
		callback->OnDestroy();
		InputSystem::Get()->RemoveListener(this);
		Running = false;
	}

	void Window::OnEnter()
	{
		isFocused = true;
		InputSystem::Get()->AddListener(this);
		callback->OnEnter();
	}

	void Window::OnLeave()
	{
		isFocused = false;
		callback->OnLeave();
	}

	void Window::OnKeyDown(int key)
	{
		callback->OnKeyDown(key);
	}

	void Window::OnKeyUp(int key)
	{
		callback->OnKeyUp(key);
	}

	void Window::OnMouseMove(const Point& delta_mouse_pos)
	{
		callback->OnMouseMove(delta_mouse_pos);
	}

	void Window::OnMouseLeftButtonDown(const Point& delta_mouse_pos)
	{
		callback->OnMouseLeftButtonDown(delta_mouse_pos);
	}

	void Window::OnMouseLeftButtonUp(const Point& delta_mouse_pos)
	{
		callback->OnMouseLeftButtonUp(delta_mouse_pos);
	}

	void Window::OnMouseRightButtonDown(const Point& delta_mouse_pos)
	{
		callback->OnMouseRightButtonDown(delta_mouse_pos);
	}

	void Window::OnMouseRightButtonUp(const Point& delta_mouse_pos)
	{
		callback->OnMouseRightButtonUp(delta_mouse_pos);
	}
}