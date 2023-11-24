// Copyright (c) 2023 snakEZ
// All rights reserved

#pragma once
#include "Math/Point.h"

class InputListener
{
public:
	InputListener() {}
	~InputListener() {}

	//KEYBOARD
	virtual void OnKeyDown(int key) = 0;
	virtual void OnKeyUp(int key) = 0;

	//MOUSE
	virtual void OnMouseMove(const Point& mouse_pos) = 0;
	virtual void OnMouseLeftButtonDown(const Point& delta_mouse_pos) = 0;
	virtual void OnMouseLeftButtonUp(const Point& delta_mouse_pos) = 0;
	virtual void OnMouseRightButtonDown(const Point& delta_mouse_pos) = 0;
	virtual void OnMouseRightButtonUp(const Point& delta_mouse_pos) = 0;
};