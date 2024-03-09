#pragma once

#include "api.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "Matrix4x4.h"
#include "Prerequisites.h"

EXTERN API void UpdateMovementParameters(Viewport* vp, float forward, float rightward);
EXTERN API void UpdateRotateParameters(Viewport* vp, float camx, float camy);
EXTERN API void SetFullscreenMode(Viewport* vp, bool isFullScr, int winWidth, int winHeight);

EXTERN API class Viewport
{
public:
	API Viewport(void* hWnd, void* engine, bool isBorder);
	API ~Viewport();

	// Scene
	void Update();
	void Render();
	void UpdateModel(const MeshPtr& mesh, const std::vector<MaterialPtr>& materialSet);
	void UpdateCamera();
	void UpdateLight();
	void DrawMesh(const MeshPtr& mesh, const std::vector<MaterialPtr>& materialSet);

	// Load
	void LoadMaterials();
	void LoadModels();
	void LoadMap();

	// Inherited via Window
	API void OnCreate();
	API void OnUpdate();
	API void OnResize(int width, int height);
	API void OnChangeLocation(int x, int y);
	API void OnDestroy();
	API void OnEnter();
	API void OnLeave();

	//API
	void RecreateSwapChain();

#ifdef _USRDLL

	UINT winw;
	UINT winh;

#endif

	bool m_vsync = false;

public:
	HWND _hWnd;
	GraphicsEngine* _enginePtr = nullptr;
	bool m_is_running = true;

	SwapChainPtr m_swap_chain;
	IndexBufferPtr m_ib;

	TexturePtr model_textureSet[6];
	TexturePtr terrain_textureSet[6];
	TexturePtr skydome_textureSet[6];

	MeshPtr m_mesh_model;
	MeshPtr m_mesh_terrain;
	MeshPtr m_mesh_skydome;

	MaterialPtr m_mat_model1;
	MaterialPtr m_mat_model2;
	MaterialPtr m_mat_model3;
	MaterialPtr m_mat_terrain;
	MaterialPtr m_mat_skydome;

	std::vector<MaterialPtr> m_material_list;

	Vector4D m_light_position;

	bool is_play = false;;
	bool keyz = false;;
	bool is_fullscr = false;
	bool keyflscr = false;

	float m_scale = 1;

	float m_delta_time = 0;

	float m_delta_pos;
	float m_delta_scale;
	float m_delta_rot;

	float m_speed = 1;

	float m_vertical_constraint = 1.5f;

	float cam_x;
	float cam_y;

	float m_light_rot_y = 0.0f;
	float m_test_rot_y = 0.0f;
	float m_forward = 0.0f;
	float m_rightward = 0.0f;

	float m_sensitivity = 0.1f;

	float m_time = 0.0f;
	float m_light_radius = 4.0f;
	float m_attenuation = 2.0f;
	bool m_anim = false;

	Matrix4x4 m_world_camera;
	Matrix4x4 m_view_camera;
	Matrix4x4 m_proj_camera;
};