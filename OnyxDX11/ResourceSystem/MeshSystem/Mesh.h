#pragma once
#pragma comment(lib, "d3d11.lib")

#include "ResourceSystem/Resource.h"
#include "RenderSystem/VertexBuffer.h"
#include "RenderSystem/IndexBuffer.h"
#include "RenderSystem/Prerequisites.h"
#include "Math/Vector3D.h"

#include <d3d11.h>

class Mesh : public Resource
{
public:
	Mesh(const wchar_t* full_filename);
	~Mesh();
	void Release();

	Vector3D Position;
	Vector3D Rotation;
	Vector3D Scale;

	PixelShaderPtr ps;
	VertexShaderPtr vs;
	ConstantBufferPtr cb;

	TexturePtr texture;

	bool IsRotated = false;
	bool IsScaled = false;

	bool IsRender = true;

	const VertexBufferPtr& GetVertexBuffer();
	const IndexBufferPtr& GetIndexBuffer();

private:
	VertexBufferPtr m_vertex_buffer;
	IndexBufferPtr m_index_buffer;

	friend class DeviceContext;
};