// Copyright (c) 2023 snakEZ
// All rights reserved

#include "ResourceManager.h"

#if __cplusplus <= 201402L 
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <experimental/filesystem>
#endif

#if __cplusplus >= 201703L
#include <filesystem>
#endif

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
}

ResourcePtr ResourceManager::CreateResourceFromFile(const wchar_t* filename)
{
	std::wstring full_filename = std::experimental::filesystem::absolute(filename);

	auto it = m_map_resources.find(filename);

	if (it != m_map_resources.end())
		return it->second;

	Resource* raw_res = this->CreateResourceFromFileConcrete(full_filename.c_str());
	if (raw_res)
	{
		ResourcePtr res(raw_res);
		m_map_resources[full_filename] = res;
		return res;
	}

	return nullptr;
}