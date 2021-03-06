#include "position_mesh.h"

namespace meow {

PositionMesh::PositionMesh(std::shared_ptr<Mesh> &mesh, std::shared_ptr<IndexListMap> &vertexMap) :
	m_mesh(mesh), m_vertexMap(vertexMap) {
}

const IndexList &PositionMesh::getOriginalVertexIndicesAt(IndexType index) const {
	auto &v = findVertexAt(index);
	return findOriginalVertexIndicesByPosition(v.position);
}

std::shared_ptr<Mesh> PositionMesh::getMesh() const {
	return m_mesh;
}

const Vertex &PositionMesh::findVertexAt(IndexType index) const {
	auto &v = m_mesh->vertices->at(index);
	if (!v)
		throw new VertexNotFound();
	return *v;
}

const IndexList &PositionMesh::findOriginalVertexIndicesByPosition(const glm::vec3 &position) const {
	auto &iter = m_vertexMap->find(position);
	if (iter == m_vertexMap->end())
		throw new VertexNotFound();
	return *iter->second;
}

} // namespace meow