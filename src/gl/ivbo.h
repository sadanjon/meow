#ifndef IVBO_H 
#define IVBO_H

#include <vector>
#include "SDL_opengl.h"

namespace meow {
	
class IVBO {
public:
	virtual ~IVBO() {}

	virtual void setIndexData(const std::vector<uint32_t> &indices) = 0;
	virtual void setVertexData(const std::vector<float> &vertices) = 0;
	virtual GLuint getID() const = 0;
};

} // namespace meow

#endif // IVBO_H