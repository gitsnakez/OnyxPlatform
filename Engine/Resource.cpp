// Copyright (c) 2023 snakEZ
// All rights reserved

#include "Resource.h"

Resource::Resource(const wchar_t* full_filename, RenderSystem* rsystem): m_full_filename(full_filename), _pRenderSystem(rsystem)
{
}

Resource::~Resource()
{
}