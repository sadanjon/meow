#include "vbo_service.h"

#include "vbo.h"

namespace meow {
	
std::shared_ptr<IVBO> VBOService::create() {
	return std::make_shared<VBO>();
}

void VBOService::bindIndexVBO(const IVBO &vbo) {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo.getID());
}

void VBOService::bindVertexVBO(const IVBO &vbo) {
	glBindBuffer(GL_ARRAY_BUFFER, vbo.getID());
}

void VBOService::unbindIndexVBO() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void VBOService::unbindVertexVBO() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

} // namespace meow