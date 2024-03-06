// 2023 Code wrote by Sivkov Roman Pavlovich a.k.a snakEZ

#include "Viewport.h"
#include <Windows.h>
#include "Vector3D.h"
#include "Vector2D.h"
#include "Matrix4x4.h"
#include "vertex.h"
#include "constant.h"
#include "Mesh.h"
#include "file_reader.h"
#include "AssetLoader.h"
#include "MapLoader.h"
#include <fstream>

EXTERN API Viewport::Viewport(void* hWnd, void* engine)
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

EXTERN API Viewport::~Viewport()
{
}

void Viewport::Update()
{
	UpdateLight();
	UpdateCamera();
}

void Viewport::Render()
{
	// CLEAR THE RENDER TARGET
	_enginePtr->GetRenderSystem()->GetImmediateDeviceContext()->ClearRenderTargetColor(m_swap_chain, 0, 0, 0, 1);

	// SET VIEWPORT OF RENDER TARGET IN WHICH WE HAVE TO DRAW
	_enginePtr->GetRenderSystem()->GetImmediateDeviceContext()->SetViewportSize(winw, winh);

	// COMPUT TRANSFORM MATRICES
	Update();

	// Model
	m_material_list.clear();
	m_material_list.push_back(m_mat_model1);
	m_material_list.push_back(m_mat_model2);
	m_material_list.push_back(m_mat_model3);
	UpdateModel(m_mesh_model, m_material_list);
	DrawMesh(m_mesh_model, m_material_list);

	// Terrain
	m_material_list.clear();
	m_material_list.push_back(m_mat_terrain);
	UpdateModel(m_mesh_terrain, m_material_list);
	DrawMesh(m_mesh_terrain, m_material_list);

	// Sky
	m_material_list.clear();
	m_material_list.push_back(m_mat_skydome);
	UpdateModel(m_mesh_skydome, m_material_list);
	DrawMesh(m_mesh_skydome, m_material_list);

	m_material_list.clear();

	m_swap_chain->Present(m_vsync);
}

EXTERN API void RenderMesh(Viewport* vp, bool isrender)
{
	vp->m_mesh_model->IsRender = isrender;
}

void Viewport::UpdateModel(const MeshPtr& mesh, const std::vector<MaterialPtr>& materialSet)
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
	temp.SetTranslation(mesh->Position);
	cc.m_world *= temp;

	temp.SetIdentity();
	temp.SetRotation(mesh->Rotation);
	cc.m_world *= temp;

	temp.SetIdentity();
	temp.SetScale(mesh->Scale);
	cc.m_world *= temp;

	cc.m_light_position = m_light_position;
	cc.m_light_radius = m_light_radius;
	cc.m_light_direction = m_light_rot_matrix.GetZDirection();
	cc.m_time = m_time;

	for (size_t m = 0; m < materialSet.size(); m++)
	{
		materialSet[m]->SetData(&cc, sizeof(constant));
	}
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
	World_Cam.SetTranslation(new_cam_pos);
	m_world_camera = World_Cam;
	World_Cam.Inverse();
	m_view_camera = World_Cam;

	// Orthographic camera
	/*m_proj_camera.SetOrthoLH((float)winw, (float)winh, 0.1f, -1);*/

	//Perspective camera
	m_proj_camera.SetPerspectiveFovLH(1.0f, ((float)winw / (float)winh), 0.1f, -1);
}

void Viewport::UpdateLight()
{
	Vector3D campos = m_world_camera.GetTranslation();
	m_light_position = Vector4D(campos.m_x, campos.m_y, campos.m_z, 1.0f);
}

void Viewport::DrawMesh(const MeshPtr& mesh, const std::vector<MaterialPtr>& materialSet)
{
	//SET THE VERTICES OF THE TRIANGLE TO DRAW
	_enginePtr->GetRenderSystem()->GetImmediateDeviceContext()->SetVertexBuffer(mesh->GetVertexBuffer());

	//SET THE INDICES OF THE TRIANGLE TO DRAW
	_enginePtr->GetRenderSystem()->GetImmediateDeviceContext()->SetIndexBuffer(mesh->GetIndexBuffer());

	for (size_t m = 0; m < mesh->GetNumMaterialSlots(); m++)
	{
		if (m >= materialSet.size()) break;

		MaterialSlot mSlot = mesh->GetMaterialSlot(m);
		_enginePtr->SetMaterial(materialSet[m]);

		// FINALLY DRAW THE TRIANGLE
		_enginePtr->GetRenderSystem()->GetImmediateDeviceContext()->DrawIndexedTriangleList(mSlot.num_indices, 0, mSlot.start_index);
	}
}

void Viewport::OnCreate()
{
	// Camera start position
	m_world_camera.SetTranslation(Vector3D(0, 1, 3));

	m_light_position = Vector4D(0, 1, 3, 1);
	m_light_radius = 40;

	AssetLoader assetLoader = AssetLoader();

	// Materials
	LoadMaterials();

	// Models
	LoadModels();

	// Object positions
	LoadMap();

	// Create swap chain
	m_swap_chain = _enginePtr->GetRenderSystem()->CreateSwapChain(_hWnd, winw, winh);
}

void Viewport::OnResize(int width, int height)
{
	//RESIZE SWAPCHAIN AND RENDER TARGET
	winw = width;
	winh = height;
	m_swap_chain->Resize(winw, winh);
	Render();
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

void Viewport::LoadMap()
{
	// Object positions
	MapLoader::Get()->LoadReadableMap(L"maps/test.map_r");

	m_mesh_model->Position = MapLoader::Get()->GetPosOfObject("MODEL");
	m_mesh_terrain->Position = MapLoader::Get()->GetPosOfObject("TERRAIN");
	m_mesh_skydome->Position = MapLoader::Get()->GetPosOfObject("SKY");
}

void Viewport::LoadMaterials()
{
	AssetLoader::Get()->LoadMaterials(L"configs/mat_assets.cfg");

	MaterialPtr mat = _enginePtr->CreateMaterial(L"shaders/PointLightVertexShader.shader", L"shaders/PointLightPixelShader.shader");
	MaterialPtr mat_bump = _enginePtr->CreateMaterial(L"shaders/dirLightVS.shader", L"shaders/dirLightPS.shader");

	// Scene
	m_mat_model1 = _enginePtr->CreateMaterial(mat_bump);
	m_mat_model1->AddTexture(AssetLoader::Get()->GetMaterial("MODEL1_COLOR"));
	m_mat_model1->AddTexture(AssetLoader::Get()->GetMaterial("MODEL1_NORMAL"));
	m_mat_model1->SetCullMode(CULL_BACK);

	m_mat_model2 = _enginePtr->CreateMaterial(mat);
	m_mat_model2->AddTexture(AssetLoader::Get()->GetMaterial("MODEL2_COLOR"));
	//m_mat_model2->AddTexture(AssetLoader::Get()->GetMaterial("MODEL2_NORMAL"));
	m_mat_model2->SetCullMode(CULL_BACK);

	m_mat_model3 = _enginePtr->CreateMaterial(mat);
	m_mat_model3->AddTexture(AssetLoader::Get()->GetMaterial("MODEL3_COLOR"));
	//m_mat_model3->AddTexture(AssetLoader::Get()->GetMaterial("MODEL3_NORMAL"));
	m_mat_model3->SetCullMode(CULL_BACK);

	// Terrain
	m_mat_terrain = _enginePtr->CreateMaterial(mat_bump);
	m_mat_terrain->AddTexture(AssetLoader::Get()->GetMaterial("TERRAIN_COLOR"));
	m_mat_terrain->AddTexture(AssetLoader::Get()->GetMaterial("TERRAIN_NORMAL"));
	m_mat_terrain->SetCullMode(CULL_BACK);

	// Sky
	m_mat_skydome = _enginePtr->CreateMaterial(mat);
	m_mat_skydome->AddTexture(AssetLoader::Get()->GetMaterial("SKY"));
	m_mat_skydome->SetCullMode(CULL_FRONT);

	m_material_list.reserve(32);
}

void Viewport::LoadModels()
{
	AssetLoader::Get()->LoadModels(L"configs/mdl_assets.cfg");

	m_mesh_model = AssetLoader::Get()->GetModel("MODEL");
	m_mesh_model->Scale = Vector3D(1, 1, 1);
	m_mesh_terrain = AssetLoader::Get()->GetModel("TERRAIN");
	m_mesh_terrain->Scale = Vector3D(1, 1, 1);
	m_mesh_skydome = AssetLoader::Get()->GetModel("SKY");
	m_mesh_skydome->Scale = Vector3D(120.0f, 120.0f, 120.0f);
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