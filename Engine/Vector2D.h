// Copyright (c) 2023 snakEZ
// All rights reserved

#include <Windows.h>

#pragma once

class Vector2D
{
public:
	Vector2D(): m_x(0), m_y(0) {};
	~Vector2D() {};
	Vector2D(float x, float y): m_x(x), m_y(y) {};
	Vector2D(const Vector2D& vector): m_x(vector.m_x), m_y(vector.m_y) {};

	static Vector2D Parse(LPCWSTR str)
	{
		return Vector2D();
	}

	Vector2D operator *(float num) const
	{
		return Vector2D(m_x * num, m_y * num);
	}

	Vector2D operator +(const Vector2D& vec) const
	{
		return Vector2D(m_x + vec.m_x, m_y + vec.m_y);
	}

	Vector2D operator -(const Vector2D& vec) const
	{
		return Vector2D(m_x - vec.m_x, m_y - vec.m_y);
	}

public:
	float m_x, m_y;
};