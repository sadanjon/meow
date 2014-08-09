#include "face_normals_generator.h"

#include "glm/geometric.hpp"

namespace meow {
	
FaceNormalsGenerator::FaceNormalsGenerator(Mesh &mesh, bool clockwiseFaces) :
	m_mesh(mesh), m_clockwiseFaces(clockwiseFaces) {

	m_newIndices = std::make_shared<IndexList>();
	m_newVertices = std::make_shared<VertexList>();
}

void FaceNormalsGenerator::generate() {
	auto triangles = createTriangles();
	IndexType i = 0;
	for (auto &triangle : *triangles) {
		createFaceNormal(*triangle);
		pushNewTriangle(*triangle, i);
		i += 1;
	}
	m_mesh.indices = m_newIndices;
	m_mesh.vertices = m_newVertices;
}

void FaceNormalsGenerator::pushNewTriangle(const VertexList &triangle, IndexType triangleIndex) {
	m_newIndices->push_back(triangleIndex * 3 + 0);
	m_newIndices->push_back(triangleIndex * 3 + 1);
	m_newIndices->push_back(triangleIndex * 3 + 2);
	m_newVertices->push_back(triangle[0]);
	m_newVertices->push_back(triangle[1]);
	m_newVertices->push_back(triangle[2]);
}



std::shared_ptr<FaceNormalsGenerator::VertexListList> FaceNormalsGenerator::createTriangles() {
	IndexType i = 0;
	auto triangles = std::make_shared<VertexListList>();
	auto triangle = std::make_shared<VertexList>();
	for (auto &index : *m_mesh.indices) {
		if (i > 0 && i % 3 == 0) {
			triangles->push_back(triangle);
			triangle = std::make_shared<VertexList>();
		}
		triangle->push_back(std::make_shared<Vertex>(*m_mesh.vertices->at(index)));
		i += 1;
	}
	return triangles;
}

void FaceNormalsGenerator::createFaceNormal(const VertexList &triangle) {
	auto &v0 = triangle[0]->position;
	auto &v1 = triangle[1]->position;
	auto &v2 = triangle[2]->position;
	auto normal = glm::normalize(glm::cross(v1 - v0, v2 - v0));
	if (m_clockwiseFaces)
		normal = -normal;
	triangle[0]->normal = normal;
	triangle[1]->normal = normal;
	triangle[2]->normal = normal;
}

} // namespace meow
