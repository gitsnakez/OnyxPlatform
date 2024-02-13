#include "Material.h"
#include "GraphicsEngine.h"
#include "RenderSystem.h"
#include "ExceptHelper.h"

Material::Material(GraphicsEngine* engine, const wchar_t* vertex_shader_path, const wchar_t* pixel_shader_path)
{
	_enginePtr = engine;

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	_enginePtr->GetRenderSystem()->CompileVertexShader(vertex_shader_path, "vsmain", &shader_byte_code, &size_shader);
	m_vertex_shader = _enginePtr->GetRenderSystem()->CreateVertexShader(shader_byte_code, size_shader);
	_enginePtr->GetRenderSystem()->ReleaseCompiledShader();

	if (!m_vertex_shader) ExceptHelper::ShowError("Material not created successfully!");

	_enginePtr->GetRenderSystem()->CompilePixelShader(pixel_shader_path, "psmain", &shader_byte_code, &size_shader);
	m_pixel_shader = _enginePtr->GetRenderSystem()->CreatePixelShader(shader_byte_code, size_shader);
	_enginePtr->GetRenderSystem()->ReleaseCompiledShader();

	if (!m_pixel_shader) ExceptHelper::ShowError("Material not created successfully!");
}

Material::Material(GraphicsEngine* engine, const MaterialPtr& material)
{
	_enginePtr = material->_enginePtr;
	m_vertex_shader = material->m_vertex_shader;
	m_pixel_shader = material->m_pixel_shader;
}

Material::~Material()
{
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
