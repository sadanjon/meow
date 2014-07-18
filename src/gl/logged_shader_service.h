#ifndef LOGGED_SHADER_SERVICE_H 
#define LOGGED_SHADER_SERVICE_H

#include <memory>
#include <string>

#include "infra/di.h"
#include "shader_service.h"
#include "ilog_service.h"

namespace meow {
	
class LoggedShaderService : public ShaderService {
	di::Component<ILogService> m_logService;
public:
	void compile(IShader &shaderId) override;

private:
	std::string getShaderInfoLog(GLint shaderId);
	int getShaderInfoLogLength(GLint shaderId);
};

} // namespace meow

#endif // LOGGED_SHADER_SERVICE_H