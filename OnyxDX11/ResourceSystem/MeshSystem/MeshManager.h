#pragma once
#include "ResourceSystem/ResourceManager.h"

class MeshManager : public ResourceManager
{
public:
	MeshManager();
	~MeshManager();
	MeshPtr CreateMeshFormFile(const wchar_t* filename);

protected:
	virtual Resource* CreateResourceFromFileConcrete(const wchar_t* filename);
};