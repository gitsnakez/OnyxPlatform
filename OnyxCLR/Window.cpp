// Copyright (c) 2023 snakEZ
// All rights reserved

#include "Window.h"
#include <Dwmapi.h>
#include "ExceptionHelper.h"
#include "InputListener.h"
#include <chrono>
#include <thread>
#include <locale>
#include <codecvt>

#define HInstance() GetModuleHandle(NULL)
#define KEYBOARD 0x00F100 //61696

// Some DWM stuff
typedef enum {
	DWMWA_BORDER_COLOR = 34,
	DWMWA_CAPTION_COLOR = 35,
	DWMWA_TEXT_COLOR = 36
} DWM_WINDOW_COLOR;

typedef enum {
	DWMWCP_DEFAULT = 0,
	DWMWCP_DONOTROUND = 1,
	DWMWCP_ROUND = 2,
	DWMWCP_ROUNDSMALL = 3
} DWM_WINDOW_CORNER_PREFERENCE;

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
			
			if (window) window->OnLeave();
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

void Window::CreateWindowForm(wstring class_name, wstring text, wstring message_box_text, BOOL is_dark_mode, UINT x, UINT y, UINT width, UINT height, HBRUSH backcolor, HICON icon, DWORD window_styles, DWORD window_ex_styles, COLORREF bordercolor, COLORREF captioncolor, COLORREF textcolor)
{
	// init info
	
	//setup converter
	using convert_type = std::codecvt_utf8<wchar_t>;
	std::wstring_convert<convert_type, wchar_t> converter;

	LPCWSTR win_classname = class_name.c_str();
	LPCWSTR win_title = text.c_str();

	std::string converted_caption = converter.to_bytes(message_box_text);

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

	if (!::RegisterClassEx(&wc)) // If registration of class will fail, the function will return false
	{
		ExceptionHelper::ThrowException("Window class failed!", converted_caption);
	}

	// Creation of the window
	Handle = CreateWindowEx(window_ex_styles, win_classname, win_title, window_styles, x, y, width, height, NULL, NULL, NULL, NULL);

	// If creation of the window fail, return false
	if (!Handle)
	{
		ExceptionHelper::ThrowException("Window handler failed!", converted_caption);
	}

	// Set title dark mode
	if (is_dark_mode)
	{
		int useImmersiveDarkMode = 1;

		if (DwmSetWindowAttribute(Handle, 19, &useImmersiveDarkMode, sizeof(int)) != 0)
			DwmSetWindowAttribute(Handle, 20, &useImmersiveDarkMode, sizeof(int));
	}
	
	OSVERSIONINFOEXW osvi = {};
	GetVersion(&osvi);

	if (osvi.dwBuildNumber >= 22000)
	{
		int cornerStyle = DWMWCP_DONOTROUND;
		DwmSetWindowAttribute(Handle, 33, &cornerStyle, sizeof(COLORREF));

		DwmSetWindowAttribute(Handle, DWMWA_BORDER_COLOR, &bordercolor, sizeof(COLORREF));
		DwmSetWindowAttribute(Handle, DWMWA_CAPTION_COLOR, &captioncolor, sizeof(COLORREF));
		DwmSetWindowAttribute(Handle, DWMWA_TEXT_COLOR, &textcolor, sizeof(COLORREF));
	}

	// Show up window
	ShowWindow(Handle, SW_SHOW);
	UpdateWindow(Handle);

	// Runnging flag status
	Running = true;
}

Window::Window()
{
	RECT rc = GetScreenRectangle();

	int center_x = (rc.right / 2) - ((STANDART_WIDTH_WITH_BORDER) / 2);
	int center_y = (rc.bottom / 2) - ((STANDART_HEIGHT_WITH_BORDER) / 2);

	CreateWindowForm(
		STANDART_WINDOW_CLASSNAME,
		STANDART_WINDOW_NAME,
		STANDART_CAPTION,
		STANDART_TITLE_BRUSH,
		center_x,
		center_y,
		STANDART_WIDTH_WITH_BORDER,
		STANDART_HEIGHT_WITH_BORDER,
		STANDART_BACKCOLOR,
		LoadIcon(NULL, IDI_APPLICATION),
		GAME_WINDOW_STYLES,
		GAME_WINDOW_EX_STYLES,
		STANDART_DWM_BORDERCOLOR,
		STANDART_DWM_CAPTIONCOLOR,
		STANDART_DWM_TEXTCOLOR);

	apiPtr = new OnyxAPIWrapper(Handle);
}

Window::Window(wstring window_classname, wstring window_title, wstring caption, BOOL darkmode, UINT x, UINT y, UINT width, UINT height, wstring icon_path)
{
	HICON icon = (HICON)LoadImage(NULL, L"bin/icon.ico", IMAGE_ICON, 32, 32, LR_LOADFROMFILE);

	CreateWindowForm(
		window_classname,
		window_title,
		caption,
		darkmode,
		x,
		y,
		width,
		height,
		STANDART_BACKCOLOR,
		icon,
		GAME_WINDOW_STYLES,
		GAME_WINDOW_EX_STYLES,
		STANDART_DWM_BORDERCOLOR,
		STANDART_DWM_CAPTIONCOLOR,
		STANDART_DWM_TEXTCOLOR);

	apiPtr = new OnyxAPIWrapper(Handle);
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
	return Handle;
}

bool Window::IsRunning()
{
	if (Running)
		Broadcast();

	return Running;
}

void Window::Start()
{
	Running = true;
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
	rc.right = ::GetSystemMetrics(SM_CXSCREEN);
	rc.top = 0;
	rc.bottom = ::GetSystemMetrics(SM_CYSCREEN);

	return rc;
}

typedef void (WINAPI* RtlGetVersion_FUNC) (OSVERSIONINFOEXW*);

BOOL Window::GetVersion(OSVERSIONINFOEX* os) {
	HMODULE hMod;
	RtlGetVersion_FUNC func;
#ifdef UNICODE
	OSVERSIONINFOEXW* osw = os;
#else
	OSVERSIONINFOEXW o;
	OSVERSIONINFOEXW* osw = &o;
#endif

	hMod = LoadLibrary(TEXT("ntdll.dll"));
	if (hMod) {
		func = (RtlGetVersion_FUNC)GetProcAddress(hMod, "RtlGetVersion");
		if (func == 0) {
			FreeLibrary(hMod);
			return FALSE;
		}
		ZeroMemory(osw, sizeof(*osw));
		osw->dwOSVersionInfoSize = sizeof(*osw);
		func(osw);
#ifndef UNICODE
		os->dwBuildNumber = osw->dwBuildNumber;
		os->dwMajorVersion = osw->dwMajorVersion;
		os->dwMinorVersion = osw->dwMinorVersion;
		os->dwPlatformId = osw->dwPlatformId;
		os->dwOSVersionInfoSize = sizeof(*os);
		DWORD sz = sizeof(os->szCSDVersion);
		WCHAR* src = osw->szCSDVersion;
		unsigned char* dtc = (unsigned char*)os->szCSDVersion;
		while (*src)
			*Dtc++ = (unsigned char)*src++;
		*Dtc = '\ 0';
#endif

	}
	else
		return FALSE;
	FreeLibrary(hMod);
	return TRUE;
}

void Window::OnCreateWindow()
{
	InputSystem::Get()->AddListener(this);
	apiPtr->OnCreate();
}

void Window::OnUpdateWindow()
{
	apiPtr->OnUpdate();
}

void Window::OnResizeWindow()
{
	apiPtr->OnResizeWindow();
}

void Window::OnChangeWindowPosition()
{
	apiPtr->OnChangeWindowPosition();
}

void Window::OnDestroyWindow()
{
	apiPtr->OnDestroy();
	InputSystem::Get()->RemoveListener(this);
	Running = false;
}

void Window::OnEnter()
{
	apiPtr->OnEnter();
	//ShowWindow(Handle, SW_MAXIMIZE);
}

void Window::OnLeave()
{
	apiPtr->OnLeave();
	//ShowWindow(Handle, SW_MINIMIZE);
}

void Window::OnKeyDown(int key)
{
	apiPtr->OnKeyDown(key);
}

void Window::OnKeyUp(int key)
{
	apiPtr->OnKeyUp(key);
}

void Window::OnMouseMove(const Point& delta_mouse_pos)
{
	apiPtr->OnMouseMove(delta_mouse_pos.m_x, delta_mouse_pos.m_y);
}

void Window::OnMouseLeftButtonDown(const Point& delta_mouse_pos)
{
	apiPtr->OnMouseButtonDown(true, delta_mouse_pos.m_x, delta_mouse_pos.m_y);
}

void Window::OnMouseLeftButtonUp(const Point& delta_mouse_pos)
{
	apiPtr->OnMouseButtonUp(true, delta_mouse_pos.m_x, delta_mouse_pos.m_y);
}

void Window::OnMouseRightButtonDown(const Point& delta_mouse_pos)
{
	apiPtr->OnMouseButtonDown(false, delta_mouse_pos.m_x, delta_mouse_pos.m_y);
}

void Window::OnMouseRightButtonUp(const Point& delta_mouse_pos)
{
	apiPtr->OnMouseButtonUp(false, delta_mouse_pos.m_x, delta_mouse_pos.m_y);
}
