#ifndef RENDERABLE_H 
#define RENDERABLE_H

#include <vector>
#include <memory>

#include "gl/ivbo.h"

#include "SDL_opengl.h"

namespace meow {

struct Surface {
	std::shared_ptr<IVBO> indexVBO;
	std::shared_ptr<IVBO> vertexVBO;

	bool hasNormals;
	bool hasUVs;
	int stride;
	int vertexCount;
	int indexCount;
};

typedef std::vector<std::shared_ptr<Surface>> SurfaceList;
	
struct Renderable {
	std::shared_ptr<SurfaceList> surfaces;
};

} // namespace meow

#endif // RENDERABLE_H