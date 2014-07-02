#ifndef MODEL_H 
#define MODEL_H

#include <vector>
#include <cstdint>
#include "vector3.h"

namespace meow {

struct Vertex;
struct Mesh;

typedef Mesh* MeshList;
typedef Vertex* VertexList;
typedef uint16_t* IndexList;

struct Vertex {
	Vector3 *position;
	Vector3 *normal;
	Vector3 *uv;
};

struct Mesh {
	/*VertexList vertices;
	IndexList indices;*/
};

struct Model {
	MeshList meshes;
};	

} // namespace meow

#endif // MODEL_H
