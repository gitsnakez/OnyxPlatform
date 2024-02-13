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

#include "api.h"
#include "Standart.h"
#include "InputListener.h"
#include <unordered_set>

namespace onyxengine
{
	class API InputSystem
	{
	public:
		InputSystem();
		~InputSystem();

		void Update();

		void AddListener(InputListener* listener);
		void RemoveListener(InputListener* listener);

		void SetCursorPosition(const Point& pos);
		void HideCursor();
		void ShowCursor();

		static InputSystem* Get();
		static void Create();
		static void Release();

	private:
		std::unordered_set<InputListener*> m_set_listeners;

		unsigned char m_keys_state[256] = {};
		unsigned char m_old_keys_state[256] = {};

		Point m_old_cursor_pos;
		bool m_first_time = true;

		static InputSystem* m_system;
	};
}