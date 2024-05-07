#pragma once
#include "VertexShader.h"
#include "PixelShader.h"
#include "Shader.h";
#include "ConstantBuffer.h"
#include <vector>

class GraphicsEngine;
class Material
{
public:
	Material(const ShaderPtr& shader);
	Material(const ShaderPtr& shader, const std::vector<TexturePtr>& textures);
	~Material();

	void AddTexture(const TexturePtr& texture);
	void RemoveTexture(unsigned int index);

	void SetData(void* data, unsigned int size);

	void SetCullMode(CULL_MODE cull_mode);
	CULL_MODE GetCullMode();

private:
	VertexShaderPtr m_vertex_shader;
	PixelShaderPtr m_pixel_shader;
	ConstantBufferPtr m_constant_buffer;
	std::vector<TexturePtr> m_vec_textures;
	GraphicsEngine* _enginePtr;

	CULL_MODE m_cull_mode = CULL_BACK;
	friend class GraphicsEngine;
};