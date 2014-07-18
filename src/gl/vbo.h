#ifndef VBO_H 
#define VBO_H

#include "ivbo.h"

#include "gl_extensions.h"

namespace meow {
	
class VBO : public IVBO {
	GLuint m_id;

public:
	VBO();
	~VBO();

	void setIndexData(const std::vector<uint32_t> &indices) override;
	void setVertexData(const std::vector<float> &vertices) override;
	GLuint getID() const override;
};

} // namespace meow

#endif // VBO_H