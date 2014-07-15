#ifndef VERTEX_INDICES_H 
#define VERTEX_INDICES_H

#include "infra/optional.h"

namespace meow {

struct VertexIndices {
	VertexIndices(Optional<int> position, Optional<int> normal,	Optional<int> uv)
	: position(position), normal(normal), uv(uv)
	{}
	Optional<int> position;
	Optional<int> normal;
	Optional<int> uv;
};

} // namespace meow

#endif // VERTEX_INDICES_H