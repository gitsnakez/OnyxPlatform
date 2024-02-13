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
#include <Windows.h>
namespace onyxengine
{
#pragma region PreInfo
	// CORNER STYLE
#define		DWM_DONOTROUND			1
#define		DWM_ROUND				2
#define		DWM_SMALLROUND			3

// IMMERSIVE MODES
#define		LIGHT_TITLEBRUSH		false
#define		DARK_TITLEBRUSH			true

// LIGHT THEME
#define		DWM_LIGHT_BORDERCOLOR	(COLORREF)(RGB(52, 52, 52))
#define		DWM_LIGHT_CAPTIONCOLOR	(COLORREF)(RGB(220, 220, 220))
#define		DWM_LIGHT_TEXTCOLOR		(COLORREF)(RGB(30, 30, 30))

// DARK THEME
#define		DWM_DARK_BORDERCOLOR	(COLORREF)(RGB(52, 52, 52))
#define		DWM_DARK_CAPTIONCOLOR	(COLORREF)(RGB(48, 48, 48))
#define		DWM_DARK_TEXTCOLOR		(COLORREF)(RGB(255, 255, 255))
#pragma endregion

// ALL STANDART INFO
#define		STANDART_WINDOW_CLASSNAME		L"ONYX_WINDOWS"
#define		STANDART_WINDOW_NAME			L"Onyx"
#define		STANDART_TITLE_BRUSH			DARK_TITLEBRUSH
#define		STANDART_X_LOCATION				CW_USEDEFAULT
#define		STANDART_Y_LOCATION				CW_USEDEFAULT
#define		STANDART_WIDTH					1280
#define		STANDART_HEIGHT					720
#define		STANDART_ICON					LoadIcon(NULL, IDI_APPLICATION)
#define		STANDART_BACKCOLOR				CreateSolidBrush(RGB(0, 0, 0))
#define		STANDART_DWM_BORDERCOLOR		DWM_DARK_BORDERCOLOR
#define		STANDART_DWM_CAPTIONCOLOR		DWM_DARK_CAPTIONCOLOR
#define		STANDART_DWM_TEXTCOLOR			DWM_DARK_TEXTCOLOR
#define		STANDART_WINDOW_STYLES			WS_OVERLAPPEDWINDOW
#define		STANDART_WINDOW_EX_STYLES		WS_EX_OVERLAPPEDWINDOW
#define		STANDART_DWMDESC				{ DWM_DONOTROUND, DARK_TITLEBRUSH, DWM_DARK_BORDERCOLOR, DWM_DARK_CAPTIONCOLOR, DWM_DARK_TEXTCOLOR }

#define		LOAD_FILE_ICON(path)			((HICON)LoadImage(NULL, path, IMAGE_ICON, 32, 32, LR_LOADFROMFILE))
#define		GAME_STYLES_NOBORDER			WS_POPUP
#define		GAME_WINDOW_STYLES				WS_CAPTION | WS_SYSMENU	| WS_MINIMIZEBOX
#define		GAME_WINDOW_EX_STYLES			0

#pragma region OutInfo
#define		STANDART_WIDTH_WITH_BORDER		(STANDART_WIDTH + 16)
#define		STANDART_HEIGHT_WITH_BORDER		(STANDART_HEIGHT + 16)
#pragma endregion
}