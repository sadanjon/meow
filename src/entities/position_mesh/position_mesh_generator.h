#ifndef POSITION_MESH_GENERATOR_H 
#define POSITION_MESH_GENERATOR_H

#include "iposition_mesh_generator_factory.h"
#include "position_mesh.h"

namespace meow {
	
class PositionMeshGenerator : public IPositionMeshGenerator {
	const Mesh &m_mesh;
	std::shared_ptr<IndexListMap> m_vertexMap;
	std::shared_ptr<Mesh> m_posMesh;
	int m_nextID;
public:
	PositionMeshGenerator(const Mesh &mesh);
	
	std::shared_ptr<IPositionMesh> generate() override;

private:
	void removeFrontIndicesFromVertexMap();
	void generatePositionMesh();
	void createEmptyPositionMesh();
	void addVertexToPositionMesh(IndexType index, const std::shared_ptr<Vertex> &vertex);
	IndexType addToVertexMapAndReturnIndex(IndexType index, const std::shared_ptr<Vertex> &vertex);
};

} // namespace meow

#endif // POSITION_MESH_GENERATOR_H