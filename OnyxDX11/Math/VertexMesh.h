// Copyright (c) 2023 snakEZ
// All rights reserved

#pragma once
#include "Vector2D.h"
#include "Vector3D.h"

class VertexMesh
{
public:
	VertexMesh() : m_position(), m_texcoord() {};
	~VertexMesh() {};
	VertexMesh(Vector3D position, Vector2D texcoord, Vector3D normal) : m_position(position), m_texcoord(texcoord), m_normal(normal) {};
	VertexMesh(const VertexMesh& vertex) : m_position(vertex.m_position), m_texcoord(vertex.m_texcoord), m_normal(vertex.m_normal) {};

public:
	Vector3D m_position;
	Vector2D m_texcoord;
	Vector3D m_normal;
};