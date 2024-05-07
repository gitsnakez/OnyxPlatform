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

#include "InputSystem.h"
#include <windef.h>
#include <Windows.h>

namespace onyxengine
{
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
		GetCursorPos(&current_cursor_pos);

		if (m_first_time) { m_old_cursor_pos = Point(current_cursor_pos.x, current_cursor_pos.y); m_first_time = false; }

		if (current_cursor_pos.x != m_old_cursor_pos.X || current_cursor_pos.y != m_old_cursor_pos.Y)
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

						if (!(*it)->isFocused)
						{
							RemoveListener(*it);
							break;
						}

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

							if (!(*it)->isFocused)
							{
								RemoveListener(*it);
								break;
							}

							++it;
						}
					}
				}
			}
			// store current keys state to old keys state buffer
			::memcpy(m_old_keys_state, m_keys_state, sizeof(unsigned char) * 256);
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
		::SetCursorPos(pos.X, pos.Y);
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
}