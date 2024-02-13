#pragma once
#include "OSharp.h"

using namespace OSharp;

public ref class IWindowCallBack : public OSharp::Interfaces::IWindowCallBack
{
public:
    virtual void ChangeWindowBorderStyles(System::IntPtr winHandle, bool showBorders);
    virtual void ChangeWindowTheme(System::IntPtr winHandle, bool isClassic);
    virtual OSharp::Interfaces::O_Location GetWindowLocation(System::IntPtr winHandle);
    virtual OSharp::Interfaces::O_Size GetWindowSize(System::IntPtr winHandle);
};