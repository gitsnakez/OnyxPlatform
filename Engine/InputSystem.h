// Copyright (c) 2023 snakEZ
// All rights reserved

#pragma once
#include "InputListener.h"
#include "Point.h"
#include <unordered_set>

class InputSystem
{
private:
	InputSystem();
	~InputSystem();

public:
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