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

namespace onyxengine
{
	class API IWindowCallback
	{
	public:
		virtual void OnCreate() = 0;
		virtual void OnUpdate() = 0;
		virtual void OnResize() = 0;
		virtual void OnChangePosition() = 0;
		virtual void OnDestroy() = 0;

		virtual void OnEnter() = 0;
		virtual void OnLeave() = 0;

		virtual void OnKeyDown(int key) = 0;
		virtual void OnKeyUp(int key) = 0;

		virtual void OnMouseMove(const Point& delta_mouse_pos) = 0;
		virtual void OnMouseLeftButtonDown(const Point& delta_mouse_pos) = 0;
		virtual void OnMouseLeftButtonUp(const Point& delta_mouse_pos) = 0;
		virtual void OnMouseRightButtonDown(const Point& delta_mouse_pos) = 0;
		virtual void OnMouseRightButtonUp(const Point& delta_mouse_pos) = 0;
	};
}