#pragma once
#include "VertexShader.h"
#include "PixelShader.h"

class GraphicsEngine;
class Material;

class Shader
{
public:
	/// <summary>
	/// Initializtion of vertex and pixel shaders.
	/// </summary>
	/// <param name="engineptr"> - Pointer to instance of graphics engine</param>
	/// <param name="vertex_shader_path"> - Vertex shader filepath</param>
	/// <param name="pixel_shader_path"> - Pixel shader filepath</param>
	Shader(GraphicsEngine* engineptr, const wchar_t* vertex_shader_path, const wchar_t* pixel_shader_path);
	~Shader();

private:
	VertexShaderPtr _pVertexShader;
	PixelShaderPtr _pPixelShader;

	GraphicsEngine* _enginePtr;

friend class GraphicsEngine;
friend class Material;
};