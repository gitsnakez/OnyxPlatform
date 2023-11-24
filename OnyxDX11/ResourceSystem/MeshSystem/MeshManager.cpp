#include "MeshManager.h"
#include "Mesh.h"

MeshManager::MeshManager()
{
}

MeshManager::~MeshManager()
{
}

MeshPtr MeshManager::CreateMeshFormFile(const wchar_t* filename)
{
	return std::static_pointer_cast<Mesh>(CreateResourceFromFile(filename));
}

Resource* MeshManager::CreateResourceFromFileConcrete(const wchar_t* filename)
{
	Mesh* mdl = nullptr;

	try
	{
		mdl = new Mesh(filename);
	}
	catch (...) {}

	return mdl;
}