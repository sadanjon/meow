#ifndef VBO_SERVICE_H 
#define VBO_SERVICE_H

#include "ivbo_service.h"

namespace meow {
	
class VBOService : public IVBOService {
public:
	std::shared_ptr<IVBO> create() override;

	void bindIndexVBO(const IVBO &vbo) override;
	void bindVertexVBO(const IVBO &vbo) override;
	void unbindIndexVBO() override;
	void unbindVertexVBO() override;
};

} // namespace meow

#endif // VBO_SERVICE_H