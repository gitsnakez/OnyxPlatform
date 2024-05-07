#pragma once

#include <string>
#include <vector>

#include "readfile.h"
#include "OnyxFileElement.h"
#include "Material.h"
#include "Mesh.h"
#include "GraphicsEngine.h"
#include "ResourceManager.h"
#include "Vector3D.h"
#include "transform.h"
#include "sstream"

#define MODELPATH L"models/"
#define MATERIALPATH L"materials/"
#define SHADERPATH L"shaders/"

std::wstring AsModel(std::wstring filename);
std::wstring AsMaterial(std::wstring filename);
std::wstring AsShader(std::wstring filename);

class Model
{
public:
	Model(OnyxFileNode& node, ResourceManager* rManager);
	~Model();
	MeshPtr GetMesh();
	std::vector<MaterialPtr> GetMaterialSet();
	const wchar_t* GetName();
	Transform* transform;

private:
	std::wstring Name;
	MeshPtr _pMesh;
	std::vector<MaterialPtr> _pMaterials;
};