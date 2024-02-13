// Copyright (c) 2023 snakEZ
// All rights reserved

#include "Window.h"
#include <Dwmapi.h>
#include "ExceptHelper.h"
#include <chrono>
#include <thread>

#define HInstance() GetModuleHandle(NULL)
#define KEYBOARD 0x00F100 //61696

LRESULT CALLBACK wndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
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
		
			break;

		case WM_MOVE:
			window = (Window*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
			if (window) window->OnChangeWindowPosition();
			break;

		
		case WM_SETFOCUS:
			// Event fired when the window is focused.
			window = (Window*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
			if(window) window->OnEnter();
			break;
		
		case WM_KILLFOCUS:
			// Event fired when the window lost focus.
			window = (Window*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
		
			window->OnLeave();
			break;
		
		case WM_DESTROY:
			// Event fired when the window is destroyed.
			window = (Window*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
			//THIS SNIPPET OF CODE WILL RECOVER THE POINTER "THIS" FROM THE SPECIAL STRUCTURE DATA IDENTIFIED BY HWND
		
			window->OnDestroyWindow();
			break;
		
		case WM_SIZE:
			// Event fired when the window resized.
			window = (Window*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
		
			if(window) window->OnResizeWindow();
			break;

	default:
		return ::DefWindowProc(hWnd, Msg, wParam, lParam);
	}

	return NULL;
}

Window::Window()
{
	winClassname = L"ANGARAENGINE_VIEWPORT_WINDOW";
	winTitle = L"GAME";
	winWidth = 1296;
	winHeight = 759;
	XLoc = CW_USEDEFAULT;
	YLoc = CW_USEDEFAULT;
	BackgroundColor = (HBRUSH)COLOR_WINDOW;
#ifdef WINAPP
	WindowStyles = WS_OVERLAPPEDWINDOW;
	exStyles = WS_EX_OVERLAPPEDWINDOW;
#elif DLLAPP
	WindowStyles = WS_POPUP;
	exStyles = 0;
#endif
	is_window_title_darkmode = true;

	WNDCLASSEX wc;
	wc.cbSize = sizeof(wc);
	wc.style = CS_OWNDC;
	wc.cbClsExtra = NULL;
	wc.cbWndExtra = NULL;
	wc.hbrBackground = BackgroundColor;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);

#ifdef WINAPP
	HICON icon = (HICON)LoadImage(NULL, L"bin/icon.ico", IMAGE_ICON, 32, 32, LR_LOADFROMFILE);
	wc.hIcon = icon;
	wc.hIconSm = icon;
#elif DLLAPP
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
#endif
	
	wc.hInstance = NULL;
	wc.lpszClassName = winClassname;
	wc.lpszMenuName = nullptr;

	wc.lpfnWndProc = wndProc;

	if (!::RegisterClassEx(&wc)) // If registration of class will fail, the function will return false
	{
		MessageBox(nullptr, L"Window:\nWindow class failed!", L"Engine", MB_OK);
		ExceptHelper::ShowError("Register window class failure!");
	}	

	// Creation of the window
	m_hwnd = ::CreateWindowEx(exStyles, winClassname, winTitle, WindowStyles, XLoc, YLoc, winWidth, winHeight, NULL, NULL, NULL, NULL);

	// Set title dark mode
	int useImmersiveDarkMode = 1;
	if (is_window_title_darkmode)
		DwmSetWindowAttribute(m_hwnd, 20, &useImmersiveDarkMode, sizeof(int)) == 0;

	// If creation of the window fail, return false
	if (!m_hwnd)
	{
		MessageBox(nullptr, L"Window:\nWindow handler failed!", L"Engine", MB_OK);
		ExceptHelper::ShowError("Window handle creation failure!");
	}

	// Show up window
	#ifdef WINAPP
	::ShowWindow(m_hwnd, SW_SHOW);
	#elif DLLAPP
	::ShowWindow(m_hwnd, SW_HIDE);
	#endif
	::UpdateWindow(m_hwnd);

	// Runnging flag status
	m_is_running = true;
}

Window::~Window()
{
	/*if (!::DestroyWindow(m_hwnd))
	{
		ExceptHelper::ShowError("Destroy window failure!");
	}*/
}

bool Window::Broadcast()
{
	MSG msg;
	if (!this->m_is_init)
	{
		SetWindowLongPtr(m_hwnd, GWLP_USERDATA, (LONG_PTR)this);
		this->OnCreateWindow();
		this->m_is_init = true;
	}

	this->OnUpdateWindow();

	while (::PeekMessage(&msg,NULL,0,0,PM_REMOVE)>0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	Sleep(1);

	return true;
}

HWND Window::GetHandler()
{
	return m_hwnd;
}

bool Window::IsRunning()
{
	if (m_is_running)
		Broadcast();

	return m_is_running;
}

RECT Window::GetClientWindowRectangle()
{
	RECT rc;
	::GetClientRect(m_hwnd, &rc);
	return rc;
}

RECT Window::GetWindowRectangle()
{
	RECT rc;
	::GetWindowRect(m_hwnd, &rc);
	return rc;
}

RECT Window::GetScreenRectangle()
{
	RECT rc;

	rc.left = 0;
	rc.right = ::GetSystemMetrics(SM_CXSCREEN);
	rc.top = 0;
	rc.bottom = ::GetSystemMetrics(SM_CYSCREEN);

	return rc;
}

void Window::OnCreateWindow()
{
}

void Window::OnUpdateWindow()
{
}

void Window::OnResizeWindow()
{
}

void Window::OnChangeWindowPosition()
{

}

void Window::OnDestroyWindow()
{
	m_is_running = false;
}

void Window::OnEnter()
{
}

void Window::OnLeave()
{
}
