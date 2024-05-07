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

#include "ResourceManager.h"

ResourceManager::ResourceManager(GraphicsEngine* gEngine) : _gEngine(gEngine)
{
}

ResourceManager::~ResourceManager()
{
	ReleaseAssets();
}

ModelPtr ResourceManager::LoadModel(OnyxFileNode& modelDesc)
{
	auto res = MakePtr(Model)(modelDesc, this);
	_modelRes[AsModel(modelDesc.GetValueByName(L"model"))] = res;
	return res;
}

FontPtr ResourceManager::LoadFont(LPCWSTR filename)
{
	return FontPtr();
}

void ResourceManager::ReloadShaders()
{
	for (const auto& [filename, shader] : _shaderRes)
	{
		auto shaderDesc = ReadFile(filename.c_str());

		*shader = Shader(
			_gEngine,
			AsShader(shaderDesc.GetValueByName(L"vertex_shader")).c_str(),
			AsShader(shaderDesc.GetValueByName(L"pixel_shader")).c_str());
	}
}

void ResourceManager::ReleaseAssets()
{
	_meshRes.clear();
	_modelRes.clear();
	_textureRes.clear();
	_materialRes.clear();
	_shaderRes.clear();
	_fontRes.clear();
}
