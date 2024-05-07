#pragma once

#include <vector>
#include <Windows.h>
#include <string>

#include "GraphicsEngine.h"
#include "RenderSystem.h"
#include "ResourceManager.h"
#include "Model.h"
#include "Vector3D.h"
#include "Prerequisites.h"

#include "OnyxFileElement.h"
#include "readfile.h"

using namespace std;

class Level
{
public:
	static void OpenLevel(const wchar_t* mapname, GraphicsEngine* graphicsEngine, LevelPtr* ptr);
	Level(const wchar_t* mapname, GraphicsEngine* graphicsEngine);
	~Level();

	vector<ModelPtr> GetModels();
	void Draw();
	void LoadAssets(OnyxFileElement* onyxElement);

	float* point_light_roty;
	float* point_light_radius;
	Vector3D* point_light;
	Vector3D* point_player_start_position;
	Vector3D* point_player_start_rotation;

private:

	wstring* Name;
	GraphicsEngine* _gEngine;
	vector<ModelPtr> _models;
};