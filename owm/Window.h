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

#pragma once

#include "Standart.h"
#include "api.h"
#include "standart_resources.h"
#include "IWindowCallback.h"
#include <Windows.h>
#include <string>
#include "InputSystem.h"

namespace onyxengine
{
	#define HInstance() GetModuleHandle(NULL)
	#define KEYBOARD 0x00F100 //61696

	using namespace std;

	EXTERN class API Window : InputListener
	{
	public:
		Window();
		Window(HWND Parent);
		Window(wstring window_classname, wstring window_title, UINT x, UINT y, UINT width, UINT height, wstring icon_path);
		Window(wstring window_classname, wstring window_title, DWORD winStyles, DWORD winExStyles, UINT x, UINT y, UINT width, UINT height, wstring icon_path);
		Window(wstring window_classname, wstring window_title, DWORD winStyles, DWORD winExStyles, UINT x, UINT y, UINT width, UINT height, wstring icon_path, bool isRectangle);
		~Window();

		HWND GetHandler();
		bool IsRunning();
		void Stop();
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
		virtual void OnResizeWindow(const Rectangle& size);
		/// <summary>
		/// Relocate window event.
		/// </summary>
		virtual void OnChangeWindowPosition(const Point& location);
		/// <summary>
		/// Closing window event.
		/// </summary>
		virtual void OnClosingWindow(bool* isCancle);
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

		IWindowCallback* callback;
		Point* Location;
		Rectangle* Size;

	private:
		bool Broadcast();

		void CreateViewportWindow(HWND Parent);
		void CreateWindowForm(wstring class_name, wstring text,
			UINT x, UINT y, UINT width,
			UINT height, HBRUSH backcolor,
			HICON icon, DWORD window_styles,
			DWORD window_ex_styles, int dwmdesc[]);

	protected:
		HWND Handle;
		bool Running = false;
		bool Initialized = false;
	};
}