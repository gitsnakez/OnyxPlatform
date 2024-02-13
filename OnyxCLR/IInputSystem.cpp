#include "IInputSystem.h"
#include "InputSystem.h"

void IInputSystem::SetCursorPosition(OSharp::Interfaces::O_Location point)
{
    InputSystem::Get()->SetCursorPosition(Point(point.X, point.Y));
}

void IInputSystem::ShowCursor()
{
    InputSystem::Get()->ShowCursor();
}

void IInputSystem::HideCursor()
{
    InputSystem::Get()->HideCursor();
}
