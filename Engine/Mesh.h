#pragma once

#include "Resource.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Prerequisites.h"
#include <vector>
#include "Vector3D.h"
#include "Vector2D.h"

#include <d3d11.h>

struct MaterialSlot
{
	size_t start_index = 0;
	size_t num_indices = 0;
	size_t material_id = 0;
};

class Mesh : public Resource
{
public:
	Mesh(const wchar_t* full_filename);
	~Mesh();

	Vector3D Position;
	Vector3D Rotation;
	Vector3D Scale;

	PixelShaderPtr ps;
	VertexShaderPtr vs;
	ConstantBufferPtr cb;

	bool IsRotated = false;
	bool IsScaled = false;

	bool IsRender = true;

	const VertexBufferPtr& GetVertexBuffer();
	const IndexBufferPtr& GetIndexBuffer();

	const MaterialSlot& GetMaterialSlot(unsigned int slot);
	size_t GetNumMaterialSlots();

private:
	void ComputeTangents(
		const Vector3D& v0, const Vector3D& v1, const Vector3D& v2,
		const Vector2D& t0, const Vector2D& t1, const Vector2D& t2,
		Vector3D& tangent, Vector3D& binormal);

	VertexBufferPtr m_vertex_buffer;
	IndexBufferPtr m_index_buffer;
	std::vector<MaterialSlot> m_material_slots;

	friend class DeviceContext;
};