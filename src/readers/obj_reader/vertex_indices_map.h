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
		return hashString(indexString(vertex->position) + indexString(vertex->normal) + indexString(vertex->uv));
	}

private:
	std::string indexString(Optional<int> i) {
		if (i.exists())
			return "[" + std::to_string(i.get()) + "]";
		else
			return "[]";
	}

	size_t hashString(std::string &str) {
		return std::hash<std::string>()(str);
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