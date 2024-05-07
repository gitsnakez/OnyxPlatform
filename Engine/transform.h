#pragma once

#include "Vector3D.h"

struct Transform
{
	Transform() : position(Vector3D(0, 0, 0)), rotation(Vector3D(0, 0, 0)), scale(Vector3D(1, 1, 1))
	{ }

	Vector3D position;
	Vector3D rotation;
	Vector3D scale;
};