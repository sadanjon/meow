#include "vertex_normals_generator.h"

#include <cstdio>

#include "glm/geometric.hpp"

#include "model.h"

namespace meow {

VertexNormalsGenerator::VertexNormalsGenerator(Mesh &mesh, bool clockwiseFaces) : m_mesh(mesh), m_clockwiseFaces(clockwiseFaces) {
}

void VertexNormalsGenerator::generate() {
	createPositionMesh();
	createVertexNormalsList();
	IndexType vertexIndex = 0;
	for (const auto &vertexNormals : m_vertexNormalsList) {
		glm::vec3 normal;
		if (vertexNormals)
			normal = averageVectors(*vertexNormals);
		else
			normal = glm::vec3(1, 0, 0);

		auto &vertexIndices = m_posMesh->getOriginalVertexIndicesAt(vertexIndex);
		for (auto i = 0; i < vertexIndices.size(); ++i) {
			auto &index = vertexIndices[i];
			m_mesh.vertices->at(index)->normal = normal;
		}
		vertexIndex += 1;
	}
}

glm::vec3 VertexNormalsGenerator::averageVectors(const std::vector<glm::vec3> &vectors) {
	glm::vec3 n(0);
	if (vectors.size() == 0)
		return n;
	for (const auto &v : vectors) {
		n += v;
	}
	n /= vectors.size();
	return n;
}

void VertexNormalsGenerator::createVertexNormalsList() {
	const Mesh &posMesh = *m_posMesh->getMesh();
	m_vertexNormalsList.resize(posMesh.vertices->size());
	std::array<glm::vec3, 3> triangle;
	for (auto i = 0U; i < posMesh.indices->size(); ++i) {
		if (i % 3 == 0 && i != 0) 
			addNormalToAllTriangleVerticesInVertexNormalsList(createNormal(triangle), i - 2);
		triangle[i % 3] = getPositionFromOffset(posMesh, i);
	}
}

void VertexNormalsGenerator::addNormalToAllTriangleVerticesInVertexNormalsList(const glm::vec3 &normal, IndexType triangleOffset) {
	const Mesh &posMesh = *m_posMesh->getMesh();
	addToVertexNormalsList(posMesh.indices->at(triangleOffset + 2), normal);
	addToVertexNormalsList(posMesh.indices->at(triangleOffset + 1), normal);
	addToVertexNormalsList(posMesh.indices->at(triangleOffset), normal);
}

glm::vec3 VertexNormalsGenerator::getPositionFromOffset(const Mesh &mesh, int offset) {
	const auto &index = mesh.indices->at(offset);
	return mesh.vertices->at(index)->position;
}

glm::vec3 VertexNormalsGenerator::createNormal(std::array<glm::vec3, 3> triangle) {
	const auto &v0 = triangle[0];
	const auto &v1 = triangle[1];
	const auto &v2 = triangle[2];
	auto normal = glm::normalize(glm::cross(v1 - v0, v2 - v0));
	if (m_clockwiseFaces)
		normal = -normal;
	return normal;
}

void VertexNormalsGenerator::addToVertexNormalsList(IndexType index, const glm::vec3 &normal) {
	if (!m_vertexNormalsList[index])
		m_vertexNormalsList[index] = std::make_shared<std::vector<glm::vec3>>();
	m_vertexNormalsList[index]->push_back(normal);
}

void VertexNormalsGenerator::createPositionMesh() {
	m_posMesh = m_positionMeshGeneratorFactory->get(m_mesh)->generate();
}



} // namespace meow
