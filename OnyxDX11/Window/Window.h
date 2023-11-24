// Copyright (c) 2023 snakEZ
// All rights reserved

#pragma once
#include <Windows.h>

class Window
{
public:
	Window();
	~Window();

	HWND GetHandler();
	bool IsRunning();
	RECT GetClientWindowRectangle();
	RECT GetWindowRectangle();
	RECT GetScreenRectangle();

	LPCWSTR winClassname;
	DWORD exStyles;
	LPCWSTR winTitle;
	int winWidth = 816;
	int winHeight = 489;
	int XLoc = CW_USEDEFAULT;
	int YLoc = CW_USEDEFAULT;
	HBRUSH BackgroundColor = (HBRUSH)COLOR_WINDOW;
	DWORD WindowStyles = WS_OVERLAPPEDWINDOW;
	bool is_window_title_darkmode = false;

	/// <summary>
	/// Create window event.
	/// </summary>
	virtual void OnCreateWindow();
	/// <summary>
	/// Update window event.
	/// </summary>
	virtual void OnUpdateWindow();
	/// <summary>
	/// Resize window event.
	/// </summary>
	virtual void OnResizeWindow();
	/// <summary>
	/// Relocate window event.
	/// </summary>
	virtual void OnChangeWindowPosition();
	/// <summary>
	/// Destroy window event.
	/// </summary>
	virtual void OnDestroyWindow();

	virtual void OnEnter();
	virtual void OnLeave();

private:
	bool Broadcast();

protected:
	HWND m_hwnd;
	bool m_is_running;
	bool m_is_init = false;
};