#ifndef POSITION_MESH 
#define POSITION_MESH

#include <unordered_map>
#include <string>

#include "glm/vec3.hpp"

#include "iposition_mesh_generator_factory.h"

namespace meow {

typedef std::unordered_map<std::string, std::shared_ptr<IndexList>> IndexListMap;

std::string vec3ToString(const glm::vec3 &v);

class PositionMesh : public IPositionMesh {
	std::shared_ptr<Mesh> m_mesh;
	std::shared_ptr<IndexListMap> m_vertexMap;
public:
	PositionMesh(std::shared_ptr<Mesh> &mesh, std::shared_ptr<IndexListMap> &vertexMap);

	const IndexList &getOriginalVertexIndicesAt(IndexType index) const override;
	std::shared_ptr<Mesh> getMesh() const override;

private:
	const Vertex &findVertexAt(IndexType index) const;
	const IndexList &findOriginalVertexIndicesByPosition(const glm::vec3 &position) const;
};

} // namespace meow

#endif // POSITION_MESH