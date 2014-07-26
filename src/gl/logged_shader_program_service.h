#ifndef LOGGED_SHADER_PROGRAM_SERVICE_H 
#define LOGGED_SHADER_PROGRAM_SERVICE_H

#include "shader_program_service.h"

#include "infra/di.h"
#include "ilog_service.h"

namespace meow {
	
class LoggedShaderProgramService : public ShaderProgramService {
	di::Component<ILogService> m_logService;
protected:
	void checkLinkStatus(GLuint programID);

private:
	std::string getProgramInfoLog(GLint programID);
	int getProgramInfoLogLength(GLint programID);
};

} // namespace meow

#endif // LOGGED_SHADER_PROGRAM_SERVICE_H