// Copyright (c) 2023 snakEZ
// All rights reserved

#pragma once

#include <cmath>

class Vector3D
{
public:
	Vector3D():m_x(0), m_y(0), m_z(0) {};
	~Vector3D() {};
	Vector3D(float x, float y, float z) :m_x(x), m_y(y), m_z(z) {};
	Vector3D(const Vector3D& vector) :m_x(vector.m_x), m_y(vector.m_y), m_z(vector.m_z) {};

	/// <summary>
	/// Linear intERPolation
	/// </summary>
	/// <param name="start_p">Start point</param>
	/// <param name="end_p">End point</param>
	/// <param name="delta">Delta time</param>
	/// <returns></returns>
	static Vector3D Lerp(const Vector3D& start_p, const Vector3D& end_p, float delta)
	{
		Vector3D vec;

		vec.m_x = start_p.m_x * (1.0f - delta) + end_p.m_x * (delta);
		vec.m_y = start_p.m_y * (1.0f - delta) + end_p.m_y * (delta);
		vec.m_z = start_p.m_z * (1.0f - delta) + end_p.m_z * (delta);

		return vec;
	}

	Vector3D operator *(float num) const
	{
		return Vector3D(m_x * num, m_y * num, m_z * num);
	}

	Vector3D operator +(const Vector3D& vec) const
	{
		return Vector3D(m_x + vec.m_x, m_y + vec.m_y, m_z + vec.m_z);
	}

	Vector3D operator -(const Vector3D& vec) const
	{
		return Vector3D(m_x - vec.m_x, m_y - vec.m_y, m_z - vec.m_z);
	}

	static Vector3D Normalize(const Vector3D& vec)
	{
		Vector3D res;
		float len = sqrt((vec.m_x * vec.m_x) + (vec.m_y * vec.m_y) + (vec.m_z * vec.m_z));

		if (!len)
			return Vector3D();

		res.m_x = vec.m_x / len;
		res.m_y = vec.m_y / len;
		res.m_z = vec.m_z / len;

		return res;
	}

	static Vector3D Cross(const Vector3D& v1, const Vector3D& v2)
	{
		Vector3D res;
		res.m_x = (v1.m_y * v2.m_z) - (v1.m_z * v2.m_y);
		res.m_y = (v1.m_z * v2.m_x) - (v1.m_x * v2.m_z);
		res.m_z = (v1.m_x * v2.m_y) - (v1.m_y * v2.m_x);
		return res;
	}

public:
	float m_x, m_y, m_z;
};