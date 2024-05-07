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

#include "ToolViewport.h"
#include "Vector3D.h"
#include "Vector2D.h"
#include "Matrix4x4.h"
#include "vertex.h"
#include "constant.h"
#include "Font.h"
#include "Font2D.h"

ToolViewport::ToolViewport(void* hWnd, void* engine)
{
	_hWnd = (HWND)hWnd;
	_enginePtr = (GraphicsEngine*)engine;

	RECT rect;
	if (GetWindowRect(_hWnd, &rect))
	{
		winw = rect.right - rect.left;
		winh = rect.bottom - rect.top;
	}
}

ToolViewport::~ToolViewport() { }


void ToolViewport::Update()
{
	UpdateLight();
	UpdateCamera();
}

void ToolViewport::Render()
{
	_enginePtr->GetRenderSystem()->GetImmediateDeviceContext()->drawcalls_iterator = 0;
	// CLEAR THE RENDER TARGET
	_enginePtr->GetRenderSystem()->GetImmediateDeviceContext()->ClearRenderTargetColor(m_swap_chain, 0, 0, 0, 1);

	// SET VIEWPORT OF RENDER TARGET IN WHICH WE HAVE TO DRAW
	_enginePtr->GetRenderSystem()->GetImmediateDeviceContext()->SetViewportSize(winw, winh);

	// COMPUTE TRANSFORM MATRICES
	Update();

	// LEVEL
	if (_level.get() != NULL)
	{
		UpdateLevel();
		_level->Draw();
	}

	m_swap_chain->Present(m_vsync);
	_enginePtr->GetRenderSystem()->ClearState();
}

void ToolViewport::UpdateCamera()
{
	Matrix4x4 World_Cam, temp;
	World_Cam.SetIdentity();

	// Set rotation by X
	temp.SetIdentity();
	temp.SetRotationX(cam_x);
	World_Cam *= temp;

	// Set rotation by Y
	temp.SetIdentity();
	temp.SetRotationY(cam_y);
	World_Cam *= temp;

	Vector3D new_cam_pos = m_world_camera.GetTranslation() + World_Cam.GetZDirection() * (m_forward);
	new_cam_pos = new_cam_pos + World_Cam.GetXDirection() * (m_rightward);

	World_Cam.SetTranslation(new_cam_pos);
	m_world_camera = World_Cam;
	World_Cam.Inverse();
	m_view_camera = World_Cam;

	//Perspective camera
	m_proj_camera.SetPerspectiveFovLH(1.0f, ((float)winw / (float)winh), 0.1f, -1);
}

void ToolViewport::UpdateLight()
{
	Vector3D campos = m_world_camera.GetTranslation();
	m_light_position = Vector4D(campos.m_x, campos.m_y, campos.m_z, 1.0f);
}

void ToolViewport::OnCreate()
{
	// Camera start position
	m_world_camera.SetTranslation(Vector3D(0, 1, 3));

	m_light_position = Vector4D(0, 1, 3, 1);
	m_light_radius = 40;

	LoadLevel(L"maps\\sdk\\showmat.level");

	// Create swap chain
	m_swap_chain = _enginePtr->GetRenderSystem()->CreateSwapChain(_hWnd, winw, winh);
}

void ToolViewport::OnResize(int width, int height)
{
	//RESIZE SWAPCHAIN AND RENDER TARGET
	if (width - 16 > 0 || height - 39 > 39)
	{
		winw = width;
		winh = height;
		m_swap_chain->Resize(winw, winh);
		Render();
	}
}

API void ToolViewport::OnChangeLocation(int x, int y)
{
	Render();
}

API void ToolViewport::SetVSync(bool value)
{
	m_vsync = value;
}

API void ToolViewport::UpdateViewport(float deltatime)
{
	m_delta_time = deltatime;
	OnUpdate();
}

API void ToolViewport::GoToZeroPos()
{
	m_proj_camera.SetTranslation(Vector3D(0, 0, 0));
	m_view_camera.SetTranslation(Vector3D(0, 0, 0));
	m_world_camera.SetTranslation(Vector3D(0, 0, 0));
}

void ToolViewport::LoadLevel(LPCWSTR filename)
{
	GraphicsEngine::Get()->isLevelLoaded = false;
	Level::OpenLevel(filename, GraphicsEngine::Get(), &_level);
}

void ToolViewport::UpdateLevel()
{
	for (size_t i = 0; i < _level->GetModels().size(); i++)
	{
		constant cc;

		Matrix4x4 m_light_rot_matrix, temp;
		m_light_rot_matrix.SetIdentity();
		m_light_rot_matrix.SetRotationY(m_light_rot_y);

		cc.m_world.SetIdentity();

		cc.m_view = m_view_camera;
		cc.m_proj = m_proj_camera;
		cc.m_camera_position = m_world_camera.GetTranslation();

		temp.SetIdentity();
		temp.SetScale(_level->GetModels()[i]->transform->scale);
		cc.m_world *= temp;

		temp.SetIdentity();
		temp.SetRotation(_level->GetModels()[i]->transform->rotation);
		cc.m_world *= temp;

		temp.SetIdentity();
		temp.SetTranslation(_level->GetModels()[i]->transform->position);
		cc.m_world *= temp;

		cc.m_light_position = m_light_position;
		cc.m_light_radius = m_light_radius;
		cc.m_light_direction = m_light_rot_matrix.GetZDirection();
		cc.m_time = m_time;

		for (size_t j = 0; j < _level->GetModels()[i]->GetMaterialSet().size(); j++)
			_level->GetModels()[i]->GetMaterialSet()[j]->SetData(&cc, sizeof(constant));
	}
}
API void ToolViewport::UnloadLevel()
{
	_level.reset();
	_enginePtr->GetResourceManager()->ReleaseAssets();
}

void ToolViewport::OnUpdate()
{
	Render();
}

void ToolViewport::OnDestroy()
{
	m_swap_chain->SetFullsceenMode(false, 1, 1);
	m_is_running = false;
	_enginePtr->Release();
}

void ToolViewport::OnEnter()
{
}

void ToolViewport::OnLeave()
{
}

void ToolViewport::RecreateSwapChain()
{
	m_swap_chain = _enginePtr->GetRenderSystem()->CreateSwapChain(_hWnd, winw, winh);
}