#include "position_mesh_generator.h"

#include <SDL_timer.h>
#include <cstdio>

namespace meow {
	
PositionMeshGenerator::PositionMeshGenerator(const Mesh &mesh) : m_mesh(mesh), m_nextID(0) {
}
	
std::shared_ptr<IPositionMesh> PositionMeshGenerator::generate() {
	generatePositionMesh();
	removeFrontIndicesFromVertexMap();
	return std::make_shared<PositionMesh>(m_posMesh, m_vertexMap);
}

void PositionMeshGenerator::removeFrontIndicesFromVertexMap() {
	for (auto &kv : *m_vertexMap) 
		kv.second = std::make_shared<IndexList>(++kv.second->begin(), kv.second->end());
}

void PositionMeshGenerator::generatePositionMesh() {
	m_vertexMap = std::make_shared<IndexListMap>();
	createEmptyPositionMesh();
	for (auto &index : *m_mesh.indices) {
		auto &vertex = m_mesh.vertices->at(index);
		addVertexToPositionMesh(index, vertex);
	}
}

void PositionMeshGenerator::createEmptyPositionMesh() {
	m_posMesh = std::make_shared<Mesh>();
	m_posMesh->indices = std::make_shared<IndexList>();
	m_posMesh->vertices = std::make_shared<VertexList>();
}

void PositionMeshGenerator::addVertexToPositionMesh(IndexType index, const std::shared_ptr<Vertex> &vertex) {
	auto newIndex = addToVertexMapAndReturnIndex(index, vertex);
	if (m_posMesh->vertices->size() <= newIndex)
		m_posMesh->vertices->resize(newIndex + 1);
	if (!m_posMesh->vertices->at(newIndex)) {
		auto newVertex = std::make_shared<Vertex>();
		newVertex->position = vertex->position;
		m_posMesh->vertices->at(newIndex) = newVertex;
	}
	m_posMesh->indices->push_back(newIndex);
}

IndexType PositionMeshGenerator::addToVertexMapAndReturnIndex(IndexType index, const std::shared_ptr<Vertex> &vertex) {
	auto &x = m_vertexMap->find(vertex->position);
	if (x == m_vertexMap->end()) {
		auto l = std::make_shared<IndexList>();
		l->push_back(m_nextID++);
		l->push_back(index);
		m_vertexMap->insert(std::make_pair(vertex->position, l));
		return l->front();
	} else {
		x->second->push_back(index);
		return x->second->front();
	}
}

} // namespace meow