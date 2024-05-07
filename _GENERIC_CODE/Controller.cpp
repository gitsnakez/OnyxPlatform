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
#include "SystemUtilities.h"

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
			// Change fullscreen mode viewport
			case 0x7A:
				FullScreen = !FullScreen;

				if (FullScreen)
				{
					//useBorders = false;
					Rectangle _primScrSize = SystemUtilities::GetPrimaryScreenSize();
					SetFullscreenMode(((Viewport*)hndDescPtr->hViewPort), FullScreen, _primScrSize.Width, _primScrSize.Height);
				}
				else
				{
					//useBorders = true;
					SetFullscreenMode(((Viewport*)hndDescPtr->hViewPort), FullScreen, ((Window*)hndDescPtr->hWin)->Size->Width, ((Window*)hndDescPtr->hWin)->Size->Height);
				}
				break;

			case 'Z': // Fly mode
				if (!keyZ)
					break;

				keyZ = true;
				playmode = !playmode;
				break;

			case 0xA0: //Sprint
				isSprint = true;
				break;

			case 0xA4: //Sprint
				isSlow = true;
				break;

			case 0x57: // Forward
				forward = movespeed * (deltatime * 16);
				break;

			case 0x41:// Left
				rightward = -movespeed * (deltatime * 16);
				break;

			case 0x53: // Back
				forward = -movespeed * (deltatime * 16);
				break;

			case 0x44: // Right
				rightward = movespeed * (deltatime * 16);
				break;

			case 0xC0: // Console
				if (!FullScreen)
					OpenTerminal();
				break;
		}
	}

	void Controller::OnKeyUp(int key)
	{
		switch (key)
		{
		case 0x57: // Forward
			movespeed = 0;
			break;

		case 0x41:// Left
			movespeed = 0;
			break;

		case 0x53: // Back
			movespeed = 0;
			break;

		case 0x44: // Right
			movespeed = 0;
			break;

		case 0xA0: //Sprint
			isSprint = false;
			break;

		case 0xA4: //Sprint
			isSlow = false;
			break;

			case 'Z':
			{
				if (playmode)
				{
					InputSystem::Get()->ShowCursor();
					playmode = false;
					rotx = oldrotx;
					roty = oldroty;
					forward = 0;
					rightward = 0;
					movespeed = 0;
				}
				else
				{
					int x = ((Window*)hndDescPtr->hWin)->Location->X;
					int y = ((Window*)hndDescPtr->hWin)->Location->Y;
					int width = ((Window*)hndDescPtr->hWin)->Size->Width;
					int height = ((Window*)hndDescPtr->hWin)->Size->Height;
					int width_center = (width - (useBorders ? 16 : 0)) / 2;
					int height_center = (height - (useBorders ? 39 : 0)) / 2;
					InputSystem::Get()->HideCursor();
					InputSystem::Get()->SetCursorPosition(Point(x + (useBorders ? 8 : 0) + width_center, y + (useBorders ? 31 : 0) + height_center));
					playmode = true;
				}
			}
		}
	}

	void Controller::OnMouseMove(const Point& delta_mouse_pos)
	{
		// Camera rotation
		if (playmode)
		{
			int loc_x = ((Window*)hndDescPtr->hWin)->Location->X;
			int loc_y = ((Window*)hndDescPtr->hWin)->Location->Y;
			int width = ((Window*)hndDescPtr->hWin)->Size->Width;
			int height = ((Window*)hndDescPtr->hWin)->Size->Height;
			int width_center = (width - (useBorders ? 16 : 0)) / 2;
			int height_center = (height - (useBorders ? 39 : 0)) / 2;

			roty += ((delta_mouse_pos.X - (loc_x + (useBorders ? 8 : 0))) - width_center) * (deltatime * sensetivity);
			rotx += ((delta_mouse_pos.Y - (loc_y + (useBorders ? 31 : 0))) - height_center) * (deltatime * sensetivity);

			if (rotx > 1.5f)
				rotx = 1.5f;
			else if (rotx < -1.5f)
				rotx = -1.5f;

			InputSystem::Get()->SetCursorPosition(Point(loc_x + (useBorders ? 8 : 0) + width_center, loc_y + (useBorders ? 31 : 0) + height_center));
		}
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