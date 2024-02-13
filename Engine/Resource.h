// Copyright (c) 2023 snakEZ
// All rights reserved

#pragma once

#include <string>
#include "Resource.h"

class Resource
{
public:
	Resource(const wchar_t* full_filename);
	virtual ~Resource();
protected:
	std::wstring m_full_filename;
};