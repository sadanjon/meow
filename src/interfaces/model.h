#ifndef MODEL_H 
#define MODEL_H

#include <vector>
#include <cstdint>

namespace meow {

struct Vertex {
	float *position;
	float *normal;
	float *uv;
};

struct Mesh {
	typedef std::vector<Vertex*> VertexList;
	typedef std::vector<uint16_t> IndexList;

	VertexList *vertices;
	IndexList *indices;
};

struct Model {
	typedef std::vector<Mesh*> MeshList;
	MeshList *meshes;
};	

} // namespace meow

#endif // MODEL_H
