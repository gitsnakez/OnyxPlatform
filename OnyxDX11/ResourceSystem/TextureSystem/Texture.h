#pragma once

#include "ResourceSystem/Resource.h"
#include "RenderSystem/Prerequisites.h"
#include <d3d11.h>

class Texture: public Resource
{
public:
	Texture(const wchar_t* full_filename);
	~Texture();
private:
	ID3D11Resource* m_texture = nullptr;
	ID3D11ShaderResourceView* m_shader_res_view = nullptr;
	ID3D11SamplerState* m_sampler_state = nullptr;

	friend class DeviceContext;
};