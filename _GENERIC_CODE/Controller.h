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

#include "defs.h"
#include "Standart.h"
#include "InputSystem.h"
#include "Window.h"
#include "Messages.h"
#include "Viewport.h"
#include <Windows.h>

namespace onyxengine
{
	class Controller
	{
	public:
		Controller(HDESC* hDesc);
		~Controller();

		void OnKeyDown(int key);
		void OnKeyUp(int key);
		void OnMouseMove(const Point& delta_mouse_pos);
		void OnMouseLeftButtonDown(const Point& delta_mouse_pos);
		void OnMouseLeftButtonUp(const Point& delta_mouse_pos);
		void OnMouseRightButtonDown(const Point& delta_mouse_pos);
		void OnMouseRightButtonUp(const Point& delta_mouse_pos);

		float deltatime = 0;
		bool playmode = false;

		// Movement
		float forward = 0;
		float rightward = 0;
		float movespeed = 0;

		// Camera
		float rotx = 0;
		float roty = 0;
		float oldrotx = 0;
		float oldroty = 0;
		float camx = 0;
		float camy = 0;

		bool keyZ = false;
		bool useBorders = true;

	private:
		HDESC* hndDescPtr;
		bool FullScreen = false;
	};
}