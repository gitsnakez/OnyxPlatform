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

#include "IWindowCallback.h"
#include "Controller.h"
#include "defs.h"
#include "Viewport.h"
#include "GraphicsEngine.h"
#include "OMath.h"
#include <cstdio>
#include <chrono>
#include <thread>

namespace onyxengine
{
	class WindowCallback : public IWindowCallback
	{
	public:
		WindowCallback(HDESC* DescHandler, Controller* control);
		WindowCallback();

		virtual void OnCreate();
		virtual void OnClosing(bool *isCancle);
		virtual void OnUpdate();

		virtual void OnResize(const Rectangle& size);
		virtual void OnChangePosition(const Point& location);
		virtual void OnDestroy();
		virtual void OnEnter();
		virtual void OnLeave();
		virtual void OnKeyDown(int key);
		virtual void OnKeyUp(int key);

		virtual void OnMouseMove(const Point& delta_mouse_pos);
		virtual void OnMouseLeftButtonDown(const Point& delta_mouse_pos);
		virtual void OnMouseLeftButtonUp(const Point& delta_mouse_pos);
		virtual void OnMouseRightButtonDown(const Point& delta_mouse_pos);
		virtual void OnMouseRightButtonUp(const Point& delta_mouse_pos);

	private:
		long old_delta = 0;
		long new_delta = 0;

		ConsoleCallback* consoleCallback;

		std::chrono::steady_clock clock;
		std::chrono::milliseconds frameTimeMin = std::chrono::milliseconds(7);

		float deltatime = 0;

		HDESC* hDesc = nullptr;
		Controller* ct;
	};
}