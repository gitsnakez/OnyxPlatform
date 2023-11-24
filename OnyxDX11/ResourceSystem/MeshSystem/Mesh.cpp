#include "Mesh.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include "SubTools/tiny_obj_loader.h"
#include "Graphics/GraphicsEngine.h"
#include "Math/VertexMesh.h"
#include "ExceptHelper.h"

#include <locale>
#include <codecvt>

Mesh::Mesh(const wchar_t* full_filename): Resource(full_filename)
{
	tinyobj::attrib_t attribs;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;

	std::string warn;
	std::string err;

	std::string inputfile = std::wstring_convert<std::codecvt_utf8<wchar_t>>().to_bytes(full_filename);

	bool rslt = tinyobj::LoadObj(&attribs, &shapes, &materials, &warn, &err, inputfile.c_str());

	if (!err.empty()) ExceptHelper::ShowError("Model wasn't loaded!");
	if (!rslt) ExceptHelper::ShowError("Model wasn't loaded!");

	// 1< shapes crush
	//if(shapes.size() > 1) ExceptHelper::ShowError("Model wasn't loaded!");

	std::vector<VertexMesh> list_vertices;
	std::vector<unsigned int> list_indices;

	//code from comment
	int vector_size = 0;
	for (size_t s = shapes.size(); s-- > 0; ) {
		vector_size += shapes[s].mesh.indices.size();
	}
	list_vertices.reserve(vector_size);
	list_indices.reserve(vector_size);
	// end

	for (size_t s = 0; s < shapes.size(); s++)
	{
		
		size_t index_offset = 0;
		// 1 Shape mode
		//list_vertices.reserve(shapes[s].mesh.indices.size());
		//list_indices.reserve(shapes[s].mesh.indices.size());

		for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++)
		{
			unsigned char num_face_verts = shapes[s].mesh.num_face_vertices[f];

			for (unsigned char v = 0; v < num_face_verts; v++)
			{
				tinyobj::index_t index = shapes[s].mesh.indices[index_offset + v];

				tinyobj::real_t vx = attribs.vertices[index.vertex_index * 3 + 0];
				tinyobj::real_t vy = attribs.vertices[index.vertex_index * 3 + 1];
				tinyobj::real_t vz = attribs.vertices[index.vertex_index * 3 + 2];

				tinyobj::real_t tx = attribs.texcoords[index.texcoord_index * 2 + 0];
				tinyobj::real_t ty = attribs.texcoords[index.texcoord_index * 2 + 1];

				tinyobj::real_t nx = attribs.normals[index.normal_index * 3 + 0];
				tinyobj::real_t ny = attribs.normals[index.normal_index * 3 + 1];
				tinyobj::real_t nz = attribs.normals[index.normal_index * 3 + 2];

				VertexMesh vertex(Vector3D(vx, vy, vz), Vector2D(tx, ty), Vector3D(nx, ny, nz));
				list_vertices.push_back(vertex);

				list_indices.push_back((unsigned int)index_offset + v);
			}

			index_offset += num_face_verts;
		}
	}

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;

	GraphicsEngine::Get()->GetVertexMeshLayoutShaderByteCodeAndSize(&shader_byte_code, &size_shader);
	m_vertex_buffer = GraphicsEngine::Get()->GetRenderSystem()->CreateVertexBuffer(&list_vertices[0], sizeof(VertexMesh), (UINT)list_vertices.size(), shader_byte_code, (UINT)size_shader);

	m_index_buffer = GraphicsEngine::Get()->GetRenderSystem()->CreateIndexBuffer(&list_indices[0], (UINT)list_indices.size());
}

const VertexBufferPtr& Mesh::GetVertexBuffer()
{
	return m_vertex_buffer;
}

const IndexBufferPtr& Mesh::GetIndexBuffer()
{
	return m_index_buffer;
}

shared_method void MeshRelease(Mesh* mesh)
{
	mesh->Release();
}

Mesh::~Mesh()
{
}

void Mesh::Release()
{
	// Nothing to release
}

shared_method void UpdateMeshInfo(Mesh* mesh, bool isrender, float transform[9])
{
	mesh->IsRender = isrender;

	mesh->Position.m_x = transform[0];
	mesh->Position.m_y = transform[1];
	mesh->Position.m_z = transform[2];

	mesh->Rotation.m_x = transform[3];
	mesh->Rotation.m_y = transform[4];
	mesh->Rotation.m_z = transform[5];

	mesh->Scale.m_x = transform[6];
	mesh->Scale.m_y = transform[7];
	mesh->Scale.m_z = transform[8];
}
