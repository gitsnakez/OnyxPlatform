// Copyright (c) 2023 snakEZ
// All rights reserved

#include "InputSystem.h"
#include <Windows.h>

InputSystem* InputSystem::m_system = nullptr;

InputSystem::InputSystem()
{
}

InputSystem::~InputSystem()
{
	InputSystem::m_system = nullptr;
}

void InputSystem::Update()
{
	POINT current_cursor_pos = {};
	::GetCursorPos(&current_cursor_pos);

	if (m_first_time) { m_old_cursor_pos = Point(current_cursor_pos.x, current_cursor_pos.y); m_first_time = false; }

	if (current_cursor_pos.x != m_old_cursor_pos.m_x || current_cursor_pos.y != m_old_cursor_pos.m_y)
	{
		// MOUSE MOVE
		std::unordered_set<InputListener*>::iterator it = m_set_listeners.begin();
		while (it != m_set_listeners.end()) {
			(*it)->OnMouseMove(Point(current_cursor_pos.x, current_cursor_pos.y));
			++it;
		}
	}
	m_old_cursor_pos = Point(current_cursor_pos.x, current_cursor_pos.y); m_first_time = false;

	if (::GetKeyboardState(m_keys_state))
	{
		for (unsigned int i = 0; i < 256; i++)
		{
			if (m_keys_state[i] & 0x80)		// KEY DOWN
			{
				std::unordered_set<InputListener*>::iterator it = m_set_listeners.begin();
				while (it != m_set_listeners.end())
				{
					if (i == VK_LBUTTON)
					{
						if (m_keys_state[i] != m_old_keys_state[i])
							(*it)->OnMouseLeftButtonDown(Point(current_cursor_pos.x, current_cursor_pos.y));
					}
					else if (i == VK_RBUTTON)
					{
						if (m_keys_state[i] != m_old_keys_state[i])
							(*it)->OnMouseRightButtonDown(Point(current_cursor_pos.x, current_cursor_pos.y));
					}
					else
						(*it)->OnKeyDown(i);

					++it;
				}
			}
			else							// KEY UP
			{
				if (m_keys_state[i] != m_old_keys_state[i])
				{
					std::unordered_set<InputListener*>::iterator it = m_set_listeners.begin();
					while (it != m_set_listeners.end())
					{
						if (i == VK_LBUTTON)
							(*it)->OnMouseLeftButtonUp(Point(current_cursor_pos.x, current_cursor_pos.y));
						else if (i == VK_RBUTTON)
							(*it)->OnMouseRightButtonUp(Point(current_cursor_pos.x, current_cursor_pos.y));
						else
							(*it)->OnKeyUp(i);
						++it;
					}
				}
			}
		}
		// store current keys state to old keys state buffer
		::memcpy(m_old_keys_state, m_keys_state, sizeof(unsigned char)  * 256);
	}
}

void InputSystem::AddListener(InputListener* listener)
{
	m_set_listeners.insert(listener);
}

void InputSystem::RemoveListener(InputListener* listener)
{
	m_set_listeners.erase(listener);
}

void InputSystem::SetCursorPosition(const Point& pos)
{
	::SetCursorPos(pos.m_x, pos.m_y);
}

void InputSystem::HideCursor()
{
	::ShowCursor(false);
}

void InputSystem::ShowCursor()
{
	::ShowCursor(true);
}

InputSystem* InputSystem::Get()
{
	return m_system;
}

void InputSystem::Create()
{
	InputSystem::m_system = new InputSystem();
}

void InputSystem::Release()
{
	if (!InputSystem::m_system) return;
	delete InputSystem::m_system;
}