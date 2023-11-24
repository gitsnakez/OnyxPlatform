#pragma once

#include "Math/Vector3D.h"
#include "SubTools/file_reader.h"

#include <map>
#include <string>
#include <vector>

class MapLoader
{
public:
	MapLoader();
	~MapLoader();

	void LoadMap(const wchar_t* filename);
	void LoadReadableMap(const wchar_t* filename);

	Vector3D GetPosOfObject(std::string objname);

	static MapLoader* Get();

private:
	std::map<std::string, Vector3D> m_positions;
};