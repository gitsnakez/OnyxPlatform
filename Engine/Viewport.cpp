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

#include "Viewport.h"
#include "EngineMath.h"
#include "Vector3D.h"
#include "Vector2D.h"
#include "Matrix4x4.h"
#include "vertex.h"
#include "constant.h"
#include "Font.h"
#include "Font2D.h"
#include <sstream>
#include <fstream>

template<typename T>
bool future_is_ready(std::future<T>* t) {
	return t->wait_for(std::chrono::seconds(0)) == std::future_status::ready;
}

EXTERN API Viewport::Viewport(void* hWnd, void* engine, bool isBorder)
{
	_hWnd = (HWND)hWnd;
	_enginePtr = (GraphicsEngine*)engine;

	RECT rect;
	if (GetWindowRect(_hWnd, &rect))
	{
		winw = rect.right - rect.left - (isBorder ? 16 : 0);
		winh = rect.bottom - rect.top - (isBorder ? 39 : 0);
	}
}

EXTERN API Viewport::~Viewport()
{
}

void Viewport::Update()
{
	/*if (!GraphicsEngine::Get()->isLevelLoaded && future_is_ready(levelLoadFuture))
		GraphicsEngine::Get()->isLevelLoaded = true;*/
	UpdateLight();
	UpdateCamera();
}

void Viewport::Render()
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

	DrawHud();
	DrawBuildInfo();
	DrawPos();
	DrawGraph();

	m_swap_chain->Present(m_vsync);
	_enginePtr->GetRenderSystem()->ClearState();
}

void Viewport::UpdateCamera()
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

	if (new_cam_pos.m_x > world_constraint) new_cam_pos.m_x = world_constraint;
	else if (new_cam_pos.m_x < -world_constraint) new_cam_pos.m_x = -world_constraint;

	if (new_cam_pos.m_y > world_constraint) new_cam_pos.m_y = world_constraint;
	else if (new_cam_pos.m_y < -world_constraint) new_cam_pos.m_y = -world_constraint;

	if (new_cam_pos.m_z > world_constraint) new_cam_pos.m_z = world_constraint;
	else if (new_cam_pos.m_z < -world_constraint) new_cam_pos.m_z = -world_constraint;

	World_Cam.SetTranslation(new_cam_pos);
	m_world_camera = World_Cam;
	World_Cam.Inverse();
	m_view_camera = World_Cam;

	// Orthographic camera
	//m_proj_camera.SetOrthoLH((float)winw / 25, (float)winh / 25, 0, 1000);

	//Perspective camera
	m_proj_camera.SetPerspectiveFovLH(1.0f, ((float)winw / (float)winh), 0.1f, -1);
}

void Viewport::UpdateLight()
{
	Vector3D campos = m_world_camera.GetTranslation();
	//m_light_rot_y = campos.m_y;
	//m_light_position = Vector4D(campos.m_x, campos.m_y, campos.m_z, 1.0f);
}

void Viewport::OnCreate()
{
	// Camera start position
	m_world_camera.SetTranslation(Vector3D(0, 0, 0));


	_pHudFont = _enginePtr->CreateUIFont(L"resources\\fonts\\HintFont.spritefont");
	_pGeneralFont = _enginePtr->CreateUIFont(L"resources\\fonts\\General.spritefont");
	_pWatermarkFont = _enginePtr->CreateUIFont(L"resources\\fonts\\WatermarkFont.spritefont");

	//LoadLevel(L"sdk/showmat");
	LoadLevel(L"devmap");

	// Create swap chain
	m_swap_chain = _enginePtr->GetRenderSystem()->CreateSwapChain(_hWnd, winw, winh);
}

void Viewport::OnResize(int width, int height)
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

API void Viewport::OnChangeLocation(int x, int y)
{
	Render();
}

EXTERN API void OnResizeViewport(Viewport* vp)
{
	return; // Obsolete code
	vp->OnResize(-1, -1);
}

EXTERN API void Viewport::ShowGraph(const int* value)
{
	isShowGraph = *value;
}

#define VERDATE "May 2024"

void Viewport::DrawGraph()
{
	if (!isShowGraph)
		return;

	auto textinfo = std::wstringstream();
	textinfo << "fps: " << (int)(1.0f / m_delta_time) << "\tframetime: " << m_delta_time << "\n";

	#if _STEAM
	textinfo << "steam client: " << *ClientName << "\n";
	#endif

	textinfo << "draw calls: " << _enginePtr->GetRenderSystem()->GetImmediateDeviceContext()->drawcalls_iterator << "\nvsync: " << (m_vsync ? "enabled" : "disabled") <<  "\n";
	textinfo << _enginePtr->GetRenderSystem()->GetGPUName();
	RECT rc = _pGeneralFont->GetBounds(textinfo.str().c_str());
	_pGeneralFont->DrawUIString(textinfo.str().c_str(), 20, (float)winh - rc.bottom - 40);
}

void Viewport::DrawBuildInfo()
{
	auto textinfo = std::wstringstream();
#if _STEAM
#if _DEBUG
	textinfo << "Steam private edition [Debug] | " << VERDATE;
#elif NDEBUG
	textinfo << "Steam private edition | " << VERDATE;
#endif
#else
#if _DEBUG
	textinfo << "Local private edition [Debug] | " << VERDATE;
#elif NDEBUG
textinfo << "Local private edition | " << VERDATE;
#endif
#endif
	RECT rc = _pWatermarkFont->GetBounds(textinfo.str().c_str());
	_pWatermarkFont->DrawUIString(textinfo.str().c_str(), 0, (float)winh - rc.bottom);
}

EXTERN API void Viewport::ShowPos(const int* value)
{
	isShowPos = *value;
}

void Viewport::DrawPos()
{
	if (!isShowPos)
		return;

	auto textinfo = std::wstringstream();
	textinfo << "Camera position:\n   x: " << EngineMath::RoundTo2(m_world_camera.GetTranslation().m_x) << " units\n   y: " << EngineMath::RoundTo2(m_world_camera.GetTranslation().m_y) << " units\n   z: " << EngineMath::RoundTo2(m_world_camera.GetTranslation().m_z) << " units\n\n";
	textinfo << "Camera rotation:\n   x: " << EngineMath::AngleAddition(m_world_camera.GetXDirection().m_x) << "° \n   y: " << EngineMath::AngleAddition(m_world_camera.GetZDirection().m_y) << "°";

	_pGeneralFont->DrawUIString(textinfo.str().c_str(), 10, 10);
}

API void Viewport::ShowHud(const int* value)
{
	isShowHud = *value;
}

void Viewport::DrawHud()
{
	if(!isShowHud)
		return;

	auto textinfo = std::wstringstream();
	textinfo << ((is_fullscr) ? "Press F11 to exit the full-screen mode" : "Press F11 to go full-screen mode");

	RECT rc = _pHudFont->GetBounds(textinfo.str().c_str());
	_pHudFont->DrawUIString(textinfo.str().c_str(), winw / 2 - rc.right / 2, 10);
}

API void Viewport::ReloadAssets()
{
	GraphicsEngine::Get()->GetResourceManager()->ReloadShaders();
}

API void Viewport::SetVSync(bool value)
{
	m_vsync = value;
}

API void Viewport::GoToZeroPos()
{
	m_proj_camera.SetTranslation(Vector3D(0, 0, 0));
	m_view_camera.SetTranslation(Vector3D(0, 0, 0));
	m_world_camera.SetTranslation(Vector3D(0, 0, 0));
}

API void Viewport::SetWireframeMode(bool value)
{
	_enginePtr->GetRenderSystem()->isWireframe = value;
}

void Viewport::LoadLevel(LPCWSTR filename)
{
	GraphicsEngine::Get()->isLevelLoaded = false;
	//delete levelLoadFuture;
	//levelLoadFuture = new std::future<void>;
	//levelLoadFuture->~future();
	//*levelLoadFuture = std::async(std::launch::async, Level::OpenLevel,  );
	Level::OpenLevel(filename, GraphicsEngine::Get(), &_level);
	m_light_position = Vector4D(*_level->point_light);
	m_light_radius = *_level->point_light_radius;
	m_light_rot_y = *_level->point_light_roty;
	m_world_camera.SetTranslation(*_level->point_player_start_position);
	cam_x = (*_level->point_player_start_rotation).m_x;
	cam_y = (*_level->point_player_start_rotation).m_y;

}

EXTERN API void LoadLevelAPI(LPCWSTR filename, Viewport* vp)
{
	vp->LoadLevel(filename);
}

void Viewport::UpdateLevel()
{
	for (size_t i = 0; i < _level->GetModels().size(); i++)
	{
		constant cc;

		Matrix4x4 m_light_rot_matrix, temp;
		m_light_rot_matrix.SetIdentity();
		m_light_rot_matrix.SetRotationY(m_light_rot_y);
		//m_light_rot_matrix.SetRotationY(1);

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
		cc.m_time = m_delta_time;

		for (size_t j = 0; j < _level->GetModels()[i]->GetMaterialSet().size(); j++)
			_level->GetModels()[i]->GetMaterialSet()[j]->SetData(&cc, sizeof(constant));
	}
}
API void Viewport::UnloadLevel()
{
	_level.reset();
	_enginePtr->GetResourceManager()->ReleaseAssets();
}

void Viewport::OnUpdate()
{
	Render();
}

EXTERN API void OnUpdateViewport(Viewport* vp, float deltaTime)
{
	vp->m_delta_time = deltaTime;
	vp->OnUpdate();
}

EXTERN API void UpdateRotateParameters(Viewport* vp, float camx, float camy)
{
	vp->cam_x = camx;
	vp->cam_y = camy;
}

EXTERN API void UpdateMovementParameters(Viewport* vp, float forward, float rightward)
{
	vp->m_forward = forward;
	vp->m_rightward = rightward;
}

void Viewport::OnDestroy()
{
	m_swap_chain->SetFullsceenMode(false, 1, 1);
	m_is_running = false;
	_enginePtr->Release();
}

EXTERN API void OnDestroyViewport(Viewport* vp)
{
	vp->OnDestroy();
}

EXTERN API void SetFullscreenMode(Viewport* vp, bool isFullScr, int winWidth, int winHeight)
{
	vp->m_swap_chain->SetFullsceenMode(isFullScr, winWidth, winHeight);
	if (isFullScr)
	{
		vp->fullScr_winw = winWidth;
		vp->fullScr_winh = winHeight;
	}

	vp->is_fullscr = isFullScr;
}

#if _STEAM
EXTERN API void SetClientName(Viewport* vp, std::wstring client)
{
	*vp->ClientName = client.c_str();
}
#endif

void Viewport::OnEnter()
{
	if (is_fullscr)
		m_swap_chain->SetFullsceenMode(is_fullscr, fullScr_winw, fullScr_winh);
}

void Viewport::OnLeave()
{
	if (is_fullscr)
	{
		ShowWindow(_hWnd, SW_MINIMIZE);
	}
}

void Viewport::RecreateSwapChain()
{
	m_swap_chain = _enginePtr->GetRenderSystem()->CreateSwapChain(_hWnd, winw, winh);
}