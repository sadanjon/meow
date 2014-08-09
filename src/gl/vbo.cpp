#include "vbo.h"

namespace meow {
	
VBO::VBO() {
	glGenBuffers(1, &m_id);
}

VBO::~VBO() {
	glDeleteBuffers(1, &m_id);
}

void VBO::setIndexData(const std::vector<IndexType> &indices) {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(IndexType) * indices.size(), indices.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void VBO::setVertexData(const std::vector<float> &vertices) {
	glBindBuffer(GL_ARRAY_BUFFER, m_id);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)* vertices.size(), vertices.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

GLuint VBO::getID() const {
	return m_id;
}

} // namespace meow