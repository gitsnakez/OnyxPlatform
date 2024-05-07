#include "Material.h"
#include "GraphicsEngine.h"
#include "RenderSystem.h"
#include "ErrorDispatcher.h"

Material::Material(const ShaderPtr& shader)
{
	_enginePtr = shader->_enginePtr;
	m_vertex_shader = shader->_pVertexShader;
	m_pixel_shader = shader->_pPixelShader;
}

Material::Material(const ShaderPtr& shader, const std::vector<TexturePtr>& textures)
{
	_enginePtr = shader->_enginePtr;
	m_vertex_shader = shader->_pVertexShader;
	m_pixel_shader = shader->_pPixelShader;

	m_vec_textures = textures;
}

Material::~Material()
{
	//for (size_t i = 0; i < m_vec_textures.size(); i++)
	//	delete m_vec_textures[i].get();
	//
	//m_vec_textures.clear();
}

void Material::AddTexture(const TexturePtr& texture)
{
	m_vec_textures.push_back(texture);
}

void Material::RemoveTexture(unsigned int index)
{
	if (index >= m_vec_textures.size()) return;
	m_vec_textures.erase(m_vec_textures.begin() + index);
}

void Material::SetData(void* data, unsigned int size)
{
	if (!m_constant_buffer) m_constant_buffer = _enginePtr->GetRenderSystem()->CreateConstantBuffer(data, size);
	else m_constant_buffer->Update(_enginePtr->GetRenderSystem()->GetImmediateDeviceContext(), data);
}

void Material::SetCullMode(CULL_MODE cull_mode)
{
	m_cull_mode = cull_mode;
}

CULL_MODE Material::GetCullMode()
{
	return m_cull_mode;
}
