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

#include "Messages.h"

namespace onyxengine
{
    EXTERN API int DisplayMessageBox(LPCWSTR message, LPCWSTR title)
    {
        int msgboxID = MessageBox(
            NULL,
            message,
            title,
            MB_ICONASTERISK | MB_OK
        );

        return msgboxID;
    }

    EXTERN API int DisplayMessageBoxWithModal(HWND modalWindow, LPCWSTR message, LPCWSTR title)
    {
        int msgboxID = MessageBox(
            modalWindow,
            message,
            title,
            MB_ICONASTERISK | MB_OK
        );

        return msgboxID;
    }

    EXTERN API int DisplayErrorMessageBox(LPCWSTR message, LPCWSTR title)
    {
        int msgboxID = MessageBox(
            NULL,
            message,
            title,
            MB_ICONERROR | MB_OK
        );

        return msgboxID;
    }

    EXTERN API int DisplayErrorMessageBoxWithModal(HWND modalWindow, LPCWSTR message, LPCWSTR title)
    {
        int msgboxID = MessageBox(
            modalWindow,
            message,
            title,
            MB_ICONERROR | MB_OK
        );

        return msgboxID;
    }
}