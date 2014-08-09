#ifndef MODEL_H 
#define MODEL_H

#include <vector>
#include <cstdint>
#include <memory>

#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include "infra/optional.h"

namespace meow {

class Vertex {
public:
	Vertex(const glm::vec3 &position, Optional<glm::vec3> &normal, Optional<glm::vec2> &uv) :
		position(position),
		normal(normal),
		uv(uv) {
	}

	Vertex() {
	}

	glm::vec3 position;
	Optional<glm::vec3> normal;
	Optional<glm::vec2> uv;
};

typedef std::vector<std::shared_ptr<Vertex>> VertexList;
typedef uint16_t IndexType;
typedef std::vector<IndexType> IndexList;

struct Mesh {
	std::shared_ptr<VertexList> vertices;
	std::shared_ptr<IndexList> indices;
};

typedef std::vector<std::shared_ptr<Mesh>> MeshList;

struct Model {
	std::shared_ptr<MeshList> meshes;
};	

} // namespace meow

#endif // MODEL_H

