#pragma once

#include "api.h"

EXTERN __interface API IGame
{
	// Inherited via Window
	void OnCreate();
	void OnUpdate();
	void OnResize(int width, int height);
	void OnChangeLocation(int x, int y);
	void OnDestroy();
	void OnEnter();
	void OnLeave();

	Matrix4x4 m_world_camera;
	Matrix4x4 m_view_camera;
	Matrix4x4 m_proj_camera;
};