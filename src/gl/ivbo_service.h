#ifndef IVBO_SERVICE_H 
#define IVBO_SERVICE_H

#include <memory>

#include "ivbo.h"

namespace meow {
	
class IVBOService {
public:
	virtual ~IVBOService() {}

	virtual std::shared_ptr<IVBO> create() = 0;
	virtual void bindIndexVBO(const IVBO &vbo) = 0;
	virtual void bindVertexVBO(const IVBO &vbo) = 0;
	virtual void unbindIndexVBO() = 0;
	virtual void unbindVertexVBO() = 0;
};

} // namespace meow

#endif // IVBO_SERVICE_H