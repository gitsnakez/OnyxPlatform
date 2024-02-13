#pragma once
#include "OSharp.h"

using namespace OSharp;

public ref class IInputSystem : public OSharp::Interfaces::IInputSystem
{
public:
    virtual void SetCursorPosition(OSharp::Interfaces::O_Location point);
    virtual void ShowCursor();
    virtual void HideCursor();
};