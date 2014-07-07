#ifndef VERTEX_MAP_H 
#define VERTEX_MAP_H

#include <cstdint>
#include <unordered_map>

#include "model.h"

namespace meow {
	
class VertexHasher {
public:
	size_t operator()(Vertex *vertex) {
		char buffer[512];
		char *b = buffer;
		b += vector3String(vertex->position, b);
		b += vector3String(vertex->normal, b);
		b += vector2String(vertex->uv, b);
		return std::hash(buffer);
	}

private:
	int vector3String(float *vector3, char *buffer) {
		if (vector3 != nullptr)
			return sprintf(buffer, "[%f%f%f]", vector3[0], vector3[1], vector3[2]);
		else
			return 0;
	}

	int vector2String(float *vector2, char *buffer) {
		if (vector2 != nullptr)
			return sprintf(buffer, "[%f%f]", vector3[0], vector3[1]);
		else
			return 0;
	}
};

class VertexComparer {
public:
	bool operator()(Vertex *a, Vertex *b) {
		return isVector3Equal(a->position, b->position) &&
			   isVector3Equal(a->normal, a->normal) &&
			   isVector2Equal(a->uv, b->uv);
	}

private:
	bool isVector3Equal(float *a, float *b) {
		if (a == nullptr && b == nullptr)
			return true;
		return a[0] == b[0] && a[1] == b[1] && a[2] == b[2];
	}

	bool isVector2Equal(float *a, float *b) {
		if (a == nullptr && b == nullptr)
			return true;
		return a[0] == b[0] && a[1] == b[1];
	}
};

typedef std::unordered_map<Vertex*, uint16_t, VertexHasher, VertexComparer> VertexMap;

} // namespace meow

#endif // VERTEX_MAP_H