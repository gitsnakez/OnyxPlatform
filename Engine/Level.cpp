#include "Level.h"

void Level::OpenLevel(const wchar_t* mapname, GraphicsEngine* graphicsEngine, LevelPtr* ptr)
{
	*ptr = MakePtr(Level)(mapname, GraphicsEngine::Get());
}

Level::Level(const wchar_t* mapname, GraphicsEngine* graphicsEngine)
{
	_gEngine = graphicsEngine;
	std::wstringstream wstrStream;
	wstrStream << L"maps\\" << mapname << L".level";
	auto LevelElement = ReadFile(wstrStream.str().c_str());
	Name = new std::wstring(LevelElement.Name);
	LoadAssets(&LevelElement);
	graphicsEngine->isLevelLoaded = true;
}

Level::~Level()
{
	_models.clear();
	delete point_light, point_player_start_position, point_light, Name;
}

vector<ModelPtr> Level::GetModels()
{
	return _models;
}

void Level::Draw()
{
	for (size_t i = 0; i < _models.size(); i++)
	{
		MeshPtr mesh = _models[i]->GetMesh();

		//SET THE VERTICES OF THE TRIANGLE TO DRAW
		_gEngine->GetRenderSystem()->GetImmediateDeviceContext()->SetVertexBuffer(mesh->GetVertexBuffer());

		//SET THE INDICES OF THE TRIANGLE TO DRAW
		_gEngine->GetRenderSystem()->GetImmediateDeviceContext()->SetIndexBuffer(mesh->GetIndexBuffer());

		for (size_t j = 0; j < mesh->GetNumMaterialSlots(); j++)
		{
			if (j >= _models[i]->GetMaterialSet().size()) break;

			MaterialSlot mSlot = mesh->GetMaterialSlot(j);
			_gEngine->SetMaterial(_models[i]->GetMaterialSet()[j]);

			// FINALLY DRAW THE TRIANGLE
			_gEngine->GetRenderSystem()->GetImmediateDeviceContext()->DrawIndexedTriangleList(mSlot.num_indices, 0, mSlot.start_index);
		}
	}
}

void Level::LoadAssets(OnyxFileElement* onyxElement)
{
	std:wstring classValue;
	for (size_t i = 0; i < onyxElement->Tree.size(); i++)
	{
		classValue = onyxElement->Tree[i].GetValueByName(L"class").c_str();

		if (classValue == L"prop_static")
			_models.push_back(_gEngine->GetResourceManager()->LoadModel(onyxElement->Tree[i]));
		else if (classValue == L"point_light")
		{
			point_light = new Vector3D();
			*point_light = Vector3D::Parse(onyxElement->Tree[i].GetNodeByName(L"transform").GetValueByName(L"position").c_str());
			point_light_roty = new float(0);
			*point_light_roty = (float)_wtof(onyxElement->Tree[i].GetValueByName(L"roty").c_str());
			point_light_radius = new float(1);
			*point_light_radius = (float)_wtof(onyxElement->Tree[i].GetValueByName(L"radius").c_str());
		}
		else if (classValue == L"point_player_start")
		{
			point_player_start_position = new Vector3D();
			*point_player_start_position = Vector3D::Parse(onyxElement->Tree[i].GetNodeByName(L"transform").GetValueByName(L"position").c_str());

			point_player_start_rotation = new Vector3D();
			*point_player_start_rotation = Vector3D::Parse(onyxElement->Tree[i].GetNodeByName(L"transform").GetValueByName(L"rotation").c_str());
		}
	}
}