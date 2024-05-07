#include "Shader.h"
#include "GraphicsEngine.h"
#include "ErrorDispatcher.h"

Shader::Shader(GraphicsEngine* engineptr, const wchar_t* vertex_shader_path, const wchar_t* pixel_shader_path)
{
	_enginePtr = engineptr;

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	_enginePtr->GetRenderSystem()->CompileVertexShader(vertex_shader_path, "vsmain", &shader_byte_code, &size_shader);
	_pVertexShader = _enginePtr->GetRenderSystem()->CreateVertexShader(shader_byte_code, size_shader);
	_enginePtr->GetRenderSystem()->ReleaseCompiledShader();

	if (!_pVertexShader) ShowErrorMessage("Shader compilation failure!");

	_enginePtr->GetRenderSystem()->CompilePixelShader(pixel_shader_path, "psmain", &shader_byte_code, &size_shader);
	_pPixelShader = _enginePtr->GetRenderSystem()->CreatePixelShader(shader_byte_code, size_shader);
	_enginePtr->GetRenderSystem()->ReleaseCompiledShader();

	if (!_pPixelShader) ShowErrorMessage("Shader compilation failure!");
}

Shader::~Shader()
{
}
