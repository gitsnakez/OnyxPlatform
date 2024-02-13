#include "MapLoader.h"
#include <Windows.h>
#include "ext_funcs.h"

MapLoader::MapLoader()
{
}

MapLoader::~MapLoader()
{
}

void MapLoader::LoadMap(const wchar_t* filename)
{
	MessageBox(nullptr, L"Cant open unreadable map yet!", L"engine", MB_OK);
}

void MapLoader::LoadReadableMap(const wchar_t* filename)
{
	file_reader freader;
	std::map<std::string, std::string> rawmap = freader.GetHeaderDictionaryFromFile(filename);

	for (const auto& pos : rawmap)
	{
		std::string* arr = SplitPosStr(pos.second);
		float poss[3];

		for (int i = 0; i < 3; i++)
		{
			poss[i] = ::atof(arr[i].c_str());
		}

		m_positions[pos.first] = Vector3D(poss[0], poss[1], poss[2]);
	}
}

Vector3D MapLoader::GetPosOfObject(std::string objname)
{
	return m_positions[objname];
}

MapLoader* MapLoader::Get()
{
	static MapLoader system;
	return &system;
}
