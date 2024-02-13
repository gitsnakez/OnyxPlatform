// Copyright (c) 2023 snakEZ
// All rights reserved

#pragma once

#include <unordered_map>
#include <string>
#include "Prerequisites.h"
#include "Resource.h"

class ResourceManager
{
public:
	ResourceManager();
	virtual ~ResourceManager();

	ResourcePtr CreateResourceFromFile(const wchar_t* filename);
protected:
	virtual Resource* CreateResourceFromFileConcrete(const wchar_t* filename) = 0;
private:
	std::unordered_map<std::wstring, ResourcePtr> m_map_resources;
};