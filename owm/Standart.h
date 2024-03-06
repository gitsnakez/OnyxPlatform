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

#include <cstdint>
#include "api.h"

namespace onyxengine
{
    API typedef uint8_t ubyte;


    EXTERN struct API Point
    {
        Point();
        Point(int x, int y);

        int X;
        int Y;
    };

    EXTERN struct API Rectangle
    {
        Rectangle();
        Rectangle(int width, int height);

        int Width;
        int Height;
    };

    struct API Brush
    {
        Brush();
        Brush(ubyte r, ubyte g, ubyte b);
        Brush(ubyte a, ubyte r, ubyte g, ubyte b);

        ubyte Alpha;
        ubyte Red;
        ubyte Green;
        ubyte Blue;

        int GetRGBHex();
    };
}