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

#include "Standart.h"

namespace onyxengine
{
    Point::Point()
    {
        X = 0;
        Y = 0;
    }

    Point::Point(int x, int y)
    {
        X = x;
        Y = y;
    }

    Rectangle::Rectangle()
    {
        Width = 0;
        Height = 0;
    }

    Rectangle::Rectangle(int width, int height)
    {
        Width = width;
        Height = height;
    }

    Brush::Brush()
    {
        Alpha = 0xFF;
        Red = 0xFF;
        Green = 0xFF;
        Blue = 0xFF;
    }

    Brush::Brush(ubyte r, ubyte g, ubyte b)
    {
        Alpha = 0xFF;
        Red = r;
        Green = g;
        Blue = b;
    }

    Brush::Brush(ubyte a, ubyte r, ubyte g, ubyte b)
    {
        Alpha = a;
        Red = r;
        Green = g;
        Blue = b;
    }

    int Brush::GetRGBHex()
    {
        return ((Red & 0xff) << 16) + ((Green & 0xff) << 8) + (Blue & 0xff);
    }
}