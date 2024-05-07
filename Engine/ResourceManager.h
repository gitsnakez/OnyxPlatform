/// Copyright (C) 2024 Roman Sivkov - All Rights Reserved.
/// You may use, distribute and modify this code under the
/// terms of the MIT License
///
/// Permission is hereby granted, free of charge, to any person obtaining a copy
/// of this software and associated documentation files(the "Software"), to deal
/// in the Software without restriction, including without limitation the rights
/// to use, copy, modify, merge, publish, distribute, sublicense, and /or sell
/// copies of the Software, and to permit persons to whom the Software is
/// furnished to do so, subject to the following conditions :
///
/// The above copyright notice and this permission notice shall be included in all
/// copies or substantial portions of the Software.
///
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
/// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
/// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
/// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
/// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
/// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
/// SOFTWARE.
///
/// For more information contact snakezfortress04@gmail.com

#pragma once

#include <vector>
#include <map>
#include <string>

#include "Mesh.h"
#include "Texture.h"
#include "Model.h"

#include "OnyxFileElement.h"
#include "RenderSystem.h"
#include "Prerequisites.h"
#include "Resource.h"

class ResourceManager
{
public:
	ResourceManager(GraphicsEngine* gEngine);
	~ResourceManager();

	ModelPtr LoadModel(OnyxFileNode& modelDesc);
	FontPtr LoadFont(LPCWSTR filename);

	void ReloadShaders();

	void ReleaseAssets();

private:
	GraphicsEngine* _gEngine;

	std::map<std::wstring, MeshPtr> _meshRes;
	std::map<std::wstring, ModelPtr> _modelRes;
	std::map<std::wstring, TexturePtr> _textureRes;
	std::map<std::wstring, MaterialPtr> _materialRes;
	std::map<std::wstring, ShaderPtr> _shaderRes;
	std::vector<FontPtr> _fontRes;

	friend class Model;
};