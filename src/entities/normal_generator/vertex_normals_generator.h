#ifndef VERTEX_NORMALS_GENERATOR_H 
#define VERTEX_NORMALS_GENERATOR_H

#include <vector>
#include <unordered_map>
#include <array>
#include <string>

#include "glm/vec3.hpp"

#include "infra/di.h"
#include "entities/position_mesh/iposition_mesh_generator_factory.h"
#include "model.h"

namespace meow {
	
class VertexNormalsGenerator {
	typedef std::vector<glm::vec3> Vec3List;
	typedef std::vector<std::shared_ptr<Vec3List>> Vec3ListList;

	di::Component<IPositionMeshGeneratorFactory> m_positionMeshGeneratorFactory;
	Mesh &m_mesh;
	std::shared_ptr<IPositionMesh> m_posMesh;
	Vec3ListList m_vertexNormalsList;
	const bool m_clockwiseFaces;
public:
	VertexNormalsGenerator(Mesh &mesh, bool clockwiseFaces);
	
	VertexNormalsGenerator(const VertexNormalsGenerator&) = delete;
	VertexNormalsGenerator &operator=(VertexNormalsGenerator) = delete;

	void generate();

private:
	glm::vec3 averageVectors(const std::vector<glm::vec3> &vectors);
	void setAllAverageNormalsToOriginalMesh();
	void setAverageNormalToOriginalMesh(IndexType vertexIndex, const Vec3List &vertexNormals);
	void addNormalToAllTriangleVerticesInVertexNormalsList(const glm::vec3 &normal, IndexType triangleOffset);
	glm::vec3 getPositionFromOffset(const Mesh &mesh, int offset);
	void createVertexNormalsList();
	void addToVertexNormalsList(IndexType index, const glm::vec3 &normal);
	glm::vec3 createNormal(std::array<glm::vec3, 3> triangle);
	void createPositionMesh();
};

} // namespace meow

#endif // VERTEX_NORMALS_GENERATOR_H