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
#include <string>
#include "Standart.h"

namespace onyxengine
{
    using namespace std;

    enum WinCornerStyle
    {
        Default = 0,
        Rectangular = 1,
        Round = 2,
        SlightlyRound = 3,
    };

    enum WinPreset
    {
        Classic = 0,
        GameReady = 1,
        Borderless = 2,
        AsViewport = 3
    };

    typedef int Style;
    typedef int ExStyle;

    #define COLORSTANDART Brush(255, 255, 255)
    #define CORNERSTANDART Default

    struct WinParams
    {
        WinParams(const wchar_t* classwchar, const wchar_t* titlewchar, int intstyles, int intexstyles, int x, int y, int width, int height);
        WinParams(WinPreset preset);

        wstring classname;
        wstring title;

        Style winstyles;
        ExStyle winexstyles;

        Point location = Point(0, 0);
        Rectangle size = Rectangle(0, 0);

    };
}