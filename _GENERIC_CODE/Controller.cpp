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

#include "Controller.h"
#include "Window.h"
#include "Messages.h"
#include <Windows.h>

namespace onyxengine
{
	Controller::Controller(HDESC* hDesc)
	{
		hndDescPtr = hDesc;
	}

	Controller::~Controller()
	{
	}

	void onyxengine::Controller::OnKeyDown(int key)
	{
		switch (key)
		{
			// Maximize viewport
			case 0x0D:
			{
				DisplayMessageBoxWithModal(((Window*)hndDescPtr->hWin)->GetHandler(), L"Key: Enter", L"Input system test");
			}
		}
	}

	void Controller::OnKeyUp(int key)
	{
	}

	void Controller::OnMouseMove(const Point& delta_mouse_pos)
	{
	}

	void Controller::OnMouseLeftButtonDown(const Point& delta_mouse_pos)
	{
	}

	void Controller::OnMouseLeftButtonUp(const Point& delta_mouse_pos)
	{
	}

	void Controller::OnMouseRightButtonDown(const Point& delta_mouse_pos)
	{
	}

	void Controller::OnMouseRightButtonUp(const Point& delta_mouse_pos)
	{
	}
}