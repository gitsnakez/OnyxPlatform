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
#include <chrono>

namespace onyxengine
{
	class WindowCallback : public IWindowCallback
	{
	public:
		WindowCallback(HDESC* hDesc, Controller* control);
		WindowCallback();

		virtual void OnCreate();
		virtual void OnUpdate();

		virtual void OnResize();
		virtual void OnChangePosition();
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
		std::chrono::steady_clock::time_point previousTime = std::chrono::steady_clock::now();
		std::chrono::steady_clock::time_point elapsed = std::chrono::steady_clock::now();

		Viewport* vp = nullptr;
		Controller* ct;
	};
}