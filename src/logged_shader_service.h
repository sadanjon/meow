#ifndef LOGGED_SHADER_SERVICE_H 
#define LOGGED_SHADER_SERVICE_H

#include "shader_service.h"
#include "ilog_service.h"

namespace meow {
	
class LoggedShaderService : public ShaderService {
	di::Component<ILogService> m_logService;
protected:
	void compileShader(GLint shaderId);

private:
	Buffer *getShaderInfoLog(GLint shaderId);
	int getShaderInfoLogLength(GLint shaderId);
};

} // namespace meow

#endif // LOGGED_SHADER_SERVICE_H