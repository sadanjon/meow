#ifndef LOGGED_SHADER_SERVICE_H 
#define LOGGED_SHADER_SERVICE_H

#include <memory>

#include "shader_service.h"
#include "ilog_service.h"
#include "infra/ibuffer_allocator.h"

namespace meow {
	
class LoggedShaderService : public ShaderService {
	di::Component<IBufferAllocator> m_bufferAllocator;
	di::Component<ILogService> m_logService;
protected:
	void compileShader(GLint shaderId);

private:
	std::shared_ptr<IBuffer> getShaderInfoLog(GLint shaderId);
	int getShaderInfoLogLength(GLint shaderId);
};

} // namespace meow

#endif // LOGGED_SHADER_SERVICE_H