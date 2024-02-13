#include "IWindowCallBack.h"
#include <Windows.h>
#include <Uxtheme.h>

void IWindowCallBack::ChangeWindowBorderStyles(System::IntPtr winHandle, bool showBorders)
{
    long s = 0;
    HWND hwnd = (HWND)(winHandle.ToPointer());

    if (showBorders)
    {
        s = GetWindowLongPtr(hwnd, GWL_EXSTYLE);
        s = s & ~(WS_EX_STATICEDGE) & ~(WS_EX_CLIENTEDGE);
        SetWindowLongPtr(hwnd, GWL_EXSTYLE, (LONG_PTR)s);

        s = GetWindowLongPtr(hwnd, GWL_STYLE);
        s = s & ~(WS_BORDER);
        SetWindowLongPtr(hwnd, GWL_STYLE, (LONG_PTR)s);
    }
    else
    {
        s = GetWindowLongPtr(hwnd, GWL_EXSTYLE) | WS_EX_CLIENTEDGE;
        SetWindowLongPtr(hwnd, GWL_EXSTYLE, (LONG_PTR)s);
    }

    //the SetWindowPos() is for update the control
    SetWindowPos(hwnd, 0, 0, 0, 0, 0,
        SWP_NOZORDER | SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE |
        SWP_DRAWFRAME | SWP_FRAMECHANGED);
}

void IWindowCallBack::ChangeWindowTheme(System::IntPtr winHandle, bool isClassic)
{
    if (isClassic)
        SetWindowTheme((HWND)(winHandle.ToPointer()), NULL, L"CLASSIC");
    else
        SetWindowTheme((HWND)(winHandle.ToPointer()), NULL, NULL);
}

OSharp::Interfaces::O_Location IWindowCallBack::GetWindowLocation(System::IntPtr winHandle)
{
    RECT rect;
    GetWindowRect((HWND)(winHandle.ToPointer()), &rect);

    return OSharp::Interfaces::O_Location(rect.left, rect.top);
}

OSharp::Interfaces::O_Size IWindowCallBack::GetWindowSize(System::IntPtr winHandle)
{
    RECT rect;
    GetWindowRect((HWND)(winHandle.ToPointer()), &rect);

    return OSharp::Interfaces::O_Size(rect.right - rect.left, rect.bottom - rect.top);
}
