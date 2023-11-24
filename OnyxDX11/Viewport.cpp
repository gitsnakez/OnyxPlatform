// Copyright (c) 2023 snakEZ
// All rights reserved

#include "Viewport.h"
#include <Windows.h>
#include "Math/Vector3D.h"
#include "Math/Vector2D.h"
#include "Math/Matrix4x4.h"
#include "ResourceSystem/MeshSystem/Mesh.h"
#include "SubTools/file_reader.h"
#include "SubTools/AssetLoader.h"
#include "SubTools/MapLoader.h"
#include <fstream>

struct vertex
{
	Vector3D position;
	Vector2D texcoord;
};

__declspec(align(16))
struct constant
{
	Matrix4x4 m_world;
	Matrix4x4 m_view;
	Matrix4x4 m_proj;
	Vector4D m_light_direction;
	Vector4D m_camera_position;
	Vector4D m_light_position = Vector4D(0, 1, 0, 0);
	float m_light_radius = 2;
	float m_time = 0;
};

Viewport::Viewport(HWND hWnd, GraphicsEngine* engine)
{
	RECT rect;
	if (GetWindowRect(hWnd, &rect))
	{
		winw = rect.right - rect.left;
		winh = rect.bottom - rect.top;
	}
	_hWnd = hWnd;
	_enginePtr = engine;
}

shared_method void* CreateViewport(HWND hWnd, GraphicsEngine* engine)
{
	return (void*) new Viewport(hWnd, engine);
}

Viewport::~Viewport()
{
}

void Viewport::Update()
{
	UpdateCamera();
	UpdateTerrain();
	UpdateSky();
}

void Viewport::Render()
{
	// CLEAR THE RENDER TARGET
	_enginePtr->GetRenderSystem()->GetImmediateDeviceContext()->ClearRenderTargetColor(m_swap_chain, 0, 0, 0, 1);

	// SET VIEWPORT OF RENDER TARGET IN WHICH WE HAVE TO DRAW
	_enginePtr->GetRenderSystem()->GetImmediateDeviceContext()->SetViewportSize(winw, winh);

	// COMPUT TRANSFORM MATRICES
	Update();

	TexturePtr list_tex[2];

	// Scene
	UpdateModelMatrix(m_model);

	// Terrain
	_enginePtr->GetRenderSystem()->SetRasterizerState(Back);
	list_tex[0] = m_terrain_mat;
	DrawMesh(m_terrain, m_vs, ps_nolight, m_terr_cb, list_tex, 1);
	list_tex->reset();

	// Sky
	list_tex[0] = m_skymat;
	_enginePtr->GetRenderSystem()->SetRasterizerState(Front);
	DrawMesh(m_skysphere, m_vs, ps_sky, m_sky_cb, list_tex, 1);

	m_swap_chain->Present(m_vsync);
}

shared_method void RenderMesh(Viewport* vp, bool isrender)
{
	vp->m_model->IsRender = isrender;
}

void Viewport::UpdateModel()
{
	constant cc;

	Matrix4x4 m_light_rot_matrix;
	m_light_rot_matrix.SetIdentity();
	m_light_rot_matrix.SetRotationY(m_light_rot_y);

	m_light_rot_y += 1.57f * m_delta_time;

	cc.m_world.SetIdentity();
	cc.m_view = m_view_camera;
	cc.m_proj = m_proj_camera;
	cc.m_camera_position = m_world_camera.GetTranslation();

	float dist_from_origin = 1.0f;

	cc.m_light_position = Vector4D(cos(m_light_rot_y) * dist_from_origin, 3.1f, sin(m_light_rot_y) * dist_from_origin, 1.0f);

	cc.m_light_radius = m_light_radius;
	cc.m_light_direction = m_light_rot_matrix.GetZDirection();
	cc.m_time = m_time;

	m_cb->Update(_enginePtr->GetRenderSystem()->GetImmediateDeviceContext(), &cc);
}

void Viewport::UpdateModelMatrix(MeshPtr mesh)
{
	if (!mesh->IsRender)
		return;

	//Pre
	constant cc;
	Matrix4x4 temp;
	TexturePtr list_tex[2];
	
	cc.m_world.SetIdentity();

	cc.m_view = m_view_camera;
	cc.m_proj = m_proj_camera;
	cc.m_camera_position = m_world_camera.GetTranslation();

	//Calcualtions
	temp.SetIdentity();
	temp.SetTranslation(mesh->Position);
	cc.m_world *= temp;

	if (mesh->IsRotated)
	{
		temp.SetIdentity();
		temp.SetRotation(mesh->Rotation);
		cc.m_world *= temp;
	}

	if (mesh->IsScaled)
	{
		temp.SetIdentity();
		temp.SetScale(mesh->Scale);
		cc.m_world *= temp;
	}

	//Constant Buffer Update
	m_cb->Update(_enginePtr->GetRenderSystem()->GetImmediateDeviceContext(), &cc);

	//Render
	_enginePtr->GetRenderSystem()->SetRasterizerState(Back);
	list_tex[0] = mesh->texture;
	DrawMesh(mesh, m_vs, ps_generic, m_cb, list_tex, 1);
	list_tex->reset();
}

void Viewport::UpdateTerrain()
{
	constant cc;
	Matrix4x4 temp;

	cc.m_world.SetIdentity();

	cc.m_view = m_view_camera;
	cc.m_proj = m_proj_camera;
	cc.m_camera_position = m_world_camera.GetTranslation();

	temp.SetIdentity();
	temp.SetScale(Vector3D(40, 20, 40));
	cc.m_world *= temp;

	temp.SetIdentity();
	temp.SetTranslation(m_pos_terrain);
	cc.m_world *= temp;

	m_terr_cb->Update(_enginePtr->GetRenderSystem()->GetImmediateDeviceContext(), &cc);
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

	Vector3D new_cam_pos = m_world_camera.GetTranslation() + World_Cam.GetZDirection() * (m_forward * 0.3f);
	new_cam_pos = new_cam_pos + World_Cam.GetXDirection() * (m_rightward * 0.3f);
	World_Cam.SetTranslation(new_cam_pos);
	m_world_camera = World_Cam;
	World_Cam.Inverse();
	m_view_camera = World_Cam;

	// Orthographic camera
	/*m_proj_camera.SetOrthoLH
	(
		width,
		height,
		0.1f,
		-1
	);*/

	//Perspective camera
	m_proj_camera.SetPerspectiveFovLH(1.0f, ((float)winw / (float)winh), 0.1f, -1);
}

void Viewport::UpdateSky()
{
	constant cc;
	Matrix4x4 temp;

	cc.m_world.SetIdentity();
	cc.m_world.SetScale(Vector3D(120.0f, 120.0f, 120.0f));

	temp.SetIdentity();
	temp.SetTranslation(m_pos_sky);
	cc.m_world *= temp;

	cc.m_view = m_view_camera;
	cc.m_proj = m_proj_camera;

	m_sky_cb->Update(_enginePtr->GetRenderSystem()->GetImmediateDeviceContext(), &cc);
}

void Viewport::DrawMesh(const MeshPtr& mesh, const VertexShaderPtr& vs, PixelShaderPtr& ps, ConstantBufferPtr& cb, const TexturePtr* list_tex, UINT num_textures)
{
	_enginePtr->GetRenderSystem()->GetImmediateDeviceContext()->SetConstantBuffer(vs, cb);
	_enginePtr->GetRenderSystem()->GetImmediateDeviceContext()->SetConstantBuffer(ps, cb);

	//SET DEFAULT SHADER IN THE GRAPHICS PIPELINE TO BE ABLE TO DRAW
	_enginePtr->GetRenderSystem()->GetImmediateDeviceContext()->SetVertexShader(vs);
	_enginePtr->GetRenderSystem()->GetImmediateDeviceContext()->SetPixelShader(ps);

	_enginePtr->GetRenderSystem()->GetImmediateDeviceContext()->SetTexture(ps, list_tex, num_textures);

	//SET THE VERTICES OF THE TRIANGLE TO DRAW
	_enginePtr->GetRenderSystem()->GetImmediateDeviceContext()->SetVertexBuffer(mesh->GetVertexBuffer());

	//SET THE INDICES OF THE TRIANGLE TO DRAW
	_enginePtr->GetRenderSystem()->GetImmediateDeviceContext()->SetIndexBuffer(mesh->GetIndexBuffer());

	// FINALLY DRAW THE TRIANGLE
	_enginePtr->GetRenderSystem()->GetImmediateDeviceContext()->DrawIndexedTriangleList(mesh->GetIndexBuffer()->GetSizeIndexList(), 0, 0);
}

void Viewport::OnCreate()
{
	// Camera start position
	m_world_camera.SetTranslation(Vector3D(0, 1, 3));

	AssetLoader assetLoader = AssetLoader();

	// Materials
	LoadMaterials();

	// Models
	AssetLoader::Get()->LoadModels(L"configs/mdl_assets.cfg");
	
	m_model = AssetLoader::Get()->GetModel("MODEL");
	m_model->texture = m_material;
	m_model->Scale = Vector3D(3, 0, 0);
	m_terrain = AssetLoader::Get()->GetModel("TERRAIN");
	m_terrain->Scale = Vector3D(40, 20, 40);
	m_skysphere = AssetLoader::Get()->GetModel("SKY");

	// Object positions
	LoadMap();

	m_swap_chain = _enginePtr->GetRenderSystem()->CreateSwapChain(_hWnd, winw, winh);

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	_enginePtr->GetRenderSystem()->CompileVertexShader(L"shaders/PointLightVertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	m_vs = _enginePtr->GetRenderSystem()->CreateVertexShader(shader_byte_code, size_shader);
	_enginePtr->GetRenderSystem()->ReleaseCompiledShader();

	_enginePtr->GetRenderSystem()->CompilePixelShader(L"shaders/PointLightPixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	ps_generic = _enginePtr->GetRenderSystem()->CreatePixelShader(shader_byte_code, size_shader);
	_enginePtr->GetRenderSystem()->ReleaseCompiledShader();

	_enginePtr->GetRenderSystem()->CompilePixelShader(L"shaders/test_nolight.shader", "psmain", &shader_byte_code, &size_shader);
	ps_nolight = _enginePtr->GetRenderSystem()->CreatePixelShader(shader_byte_code, size_shader);
	_enginePtr->GetRenderSystem()->ReleaseCompiledShader();

	_enginePtr->GetRenderSystem()->CompilePixelShader(L"shaders/Sky.shader", "psmain", &shader_byte_code, &size_shader);
	ps_sky = _enginePtr->GetRenderSystem()->CreatePixelShader(shader_byte_code, size_shader);
	_enginePtr->GetRenderSystem()->ReleaseCompiledShader();

	constant cc;

	m_cb = _enginePtr->GetRenderSystem()->CreateConstantBuffer(&cc, sizeof(constant));
	m_terr_cb = _enginePtr->GetRenderSystem()->CreateConstantBuffer(&cc, sizeof(constant));
	m_sky_cb = _enginePtr->GetRenderSystem()->CreateConstantBuffer(&cc, sizeof(constant));
}

shared_method void OnCreateViewport(Viewport* vp)
{
	vp->OnCreate();
}

void Viewport::OnResize()
{
	if (winw > 0 && winh > 0)
	{
		//RESIZE SWAPCHAIN AND RENDER TARGET
		m_swap_chain->Resize(winw, winh);
		Render();
	}
}

shared_method void OnResizeViewport(Viewport* vp)
{
	vp->OnResize();
}

void Viewport::LoadMap()
{
	// Object positions
	MapLoader::Get()->LoadReadableMap(L"maps/test.map_r");

	m_pos_model = MapLoader::Get()->GetPosOfObject("MODEL");
	m_pos_terrain = MapLoader::Get()->GetPosOfObject("TERRAIN");
	m_pos_sky = MapLoader::Get()->GetPosOfObject("SKY");
}

void Viewport::LoadMaterials()
{
	AssetLoader::Get()->LoadMaterials(L"configs/mat_assets.cfg");

	m_material = AssetLoader::Get()->GetMaterial("MODEL");
	m_terrain_mat = AssetLoader::Get()->GetMaterial("TERRAIN");
	m_skymat = AssetLoader::Get()->GetMaterial("SKY");
}

void Viewport::OnUpdate()
{
	Render();
}

shared_method void OnUpdateViewport(Viewport* vp, float deltaTime)
{
	vp->m_delta_time = deltaTime;
	vp->OnUpdate();
}

shared_method void UpdateRotateParameters(Viewport* vp, float camx, float camy)
{
	vp->cam_x = camx;
	vp->cam_y = camy;
}

shared_method void UpdateMovementParameters(Viewport* vp, float forward, float rightward)
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

shared_method void OnDestroyViewport(Viewport* vp)
{
	vp->OnDestroy();
}

shared_method void SetFullscreenMode(Viewport* vp, bool isFullScr, int winWidth, int winHeight)
{
	if(isFullScr)
		vp->m_swap_chain->SetFullsceenMode(true, winWidth, winHeight);
	else
		vp->m_swap_chain->SetFullsceenMode(false, winWidth, winHeight);
}

void Viewport::OnEnter()
{
}

void Viewport::OnLeave()
{
}

void Viewport::RecreateSwapChain()
{
	m_swap_chain = _enginePtr->GetRenderSystem()->CreateSwapChain(_hWnd, winw, winh);
}