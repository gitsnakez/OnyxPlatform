#pragma once

#include "Graphics/GraphicsEngine.h"
#include "RenderSystem/SwapChain.h"
#include "RenderSystem/DeviceContext.h"
#include "RenderSystem/VertexBuffer.h"
#include "RenderSystem/IndexBuffer.h"
#include "RenderSystem/ConstantBuffer.h"
#include "RenderSystem/VertexShader.h"
#include "RenderSystem/PixelShader.h"
#include "Math/Matrix4x4.h"
#include "RenderSystem/Prerequisites.h"

class Viewport
{
public:
	Viewport(HWND hWnd, GraphicsEngine* engine);
	~Viewport();

	// Scene
	void Update();
	void Render();
	void UpdateModel();
	void UpdateModelMatrix(MeshPtr mesh);
	void UpdateTerrain();
	void UpdateCamera();
	void UpdateSky();
	void DrawMesh(const MeshPtr& mesh, const VertexShaderPtr& vs, PixelShaderPtr& ps, ConstantBufferPtr& cb, const TexturePtr* list_tex, UINT num_textures);

	// Load
	void LoadMaterials();
	void LoadMap();

	// Inherited via Window
	void OnCreate();
	void OnUpdate();
	void OnResize();
	void OnDestroy();
	void OnEnter();
	void OnLeave();

	//API
	void RecreateSwapChain();

#ifdef DLLAPP

	UINT winw;
	UINT winh;

#endif

	bool m_vsync = false;

public:
	HWND _hWnd;
	SwapChainPtr m_swap_chain;
	VertexBufferPtr m_vb;
	ConstantBufferPtr m_cb;
	ConstantBufferPtr m_terr_cb;
	ConstantBufferPtr m_sky_cb;
	IndexBufferPtr m_ib;
	VertexShaderPtr m_vs;

	// Pixel Shaders
	PixelShaderPtr ps_generic;
	PixelShaderPtr ps_nolight;
	PixelShaderPtr ps_sky;

	TexturePtr m_material;
	TexturePtr m_terrain_mat;
	TexturePtr m_skymat;

	MeshPtr m_model;
	MeshPtr m_terrain;
	MeshPtr m_skysphere;

	Vector3D m_pos_model = Vector3D();
	Vector3D m_pos_terrain = Vector3D();
	Vector3D m_pos_sky = Vector3D();

	bool is_play = false;;
	bool keyz = false;;
	bool is_fullscr = false;
	bool keyflscr = false;

	GraphicsEngine* _enginePtr = nullptr;

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

	bool m_is_running = true;

	bool m_is_slow = false;
	bool m_is_high = false;

	Matrix4x4 m_world_camera;
	Matrix4x4 m_view_camera;
	Matrix4x4 m_proj_camera;
};