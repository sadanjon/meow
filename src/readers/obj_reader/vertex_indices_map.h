#ifndef VERTEX_MAP_H 
#define VERTEX_MAP_H

#include <cstdint>
#include <string>
#include <unordered_map>

#include "vertex_indices.h"

namespace meow {
	
class VertexIndicesHasher {
public:
	size_t operator()(const std::shared_ptr<VertexIndices> &vertex) {
		std::hash<int> h;
		return h(OptionalIntToInt(vertex->position)) ^ h(OptionalIntToInt(vertex->normal)) ^ h(OptionalIntToInt(vertex->uv));
	}

private:
	int OptionalIntToInt(Optional<int> o) {
		return o.exists() ? o.get() : -1;
	}
};

class VertexIndicesComparer {
public:
	bool operator()(const std::shared_ptr<VertexIndices> &a, const std::shared_ptr<VertexIndices> &b) {
		return a->position == b->position &&
				a->normal == b->normal &&
				a->uv == b->uv;
	}
};

typedef std::unordered_map<std::shared_ptr<VertexIndices>, int, VertexIndicesHasher, VertexIndicesComparer> VertexIndicesMap;

} // namespace meow

#endif // VERTEX_MAP_H