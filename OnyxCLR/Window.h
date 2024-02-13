// Copyright (c) 2023 snakEZ
// All rights reserved

#pragma once

#include "standart_resources.h"
#include <Windows.h>
#include "OnyxAPIWrapper.h"
#include <string>
#include "InputSystem.h"
#include "Point.h"

using namespace std;

class Window : InputListener
{
public:
	Window();
	Window(wstring window_classname, wstring window_title, wstring caption, BOOL darkmode, UINT x, UINT y, UINT width, UINT height, wstring icon_path);
	~Window();

	HWND GetHandler();
	bool IsRunning();
	void Start();
	RECT GetClientWindowRectangle();
	RECT GetWindowRectangle();
	static RECT GetScreenRectangle();

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

	// Inherited via InputListener
	virtual void OnKeyDown(int key);
	virtual void OnKeyUp(int key);

	virtual void OnMouseMove(const Point& delta_mouse_pos);
	virtual void OnMouseLeftButtonDown(const Point& delta_mouse_pos);
	virtual void OnMouseLeftButtonUp(const Point& delta_mouse_pos);
	virtual void OnMouseRightButtonDown(const Point& delta_mouse_pos);
	virtual void OnMouseRightButtonUp(const Point& delta_mouse_pos);

private:
	bool Broadcast();
	bool IsMinimized = false;
	void CreateWindowForm(wstring class_name, wstring text, wstring message_box_text, BOOL is_dark_mode, UINT x, UINT y, UINT width, UINT height, HBRUSH backcolor, HICON icon, DWORD window_styles, DWORD window_ex_styles, COLORREF bordercolor, COLORREF captioncolor, COLORREF textcolor);

protected:
	HWND Handle;
	bool Running = false;
	bool Initialized = false;
	OnyxAPIWrapper* apiPtr = nullptr;
};