#ifndef MODEL_H 
#define MODEL_H

#include <vector>
#include <cstdint>
#include <memory>

#include "math/vector3.h"
#include "math/vector2.h"
#include "infra/optional.h"

namespace meow {

class Vertex {
public:
	Vertex(Optional<Vector3> &position,	Optional<Vector3> &normal, Optional<Vector2> &uv) :
		position(position),
		normal(normal),
		uv(uv) {
	}

	Vertex() {
	}

	Optional<Vector3> position;
	Optional<Vector3> normal;
	Optional<Vector2> uv;
};

typedef std::vector<std::shared_ptr<Vertex>> VertexList;
typedef std::vector<uint32_t> IndexList;

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
