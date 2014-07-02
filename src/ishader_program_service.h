#ifndef SHADER_PROGRAM_SERVICE_H 
#define SHADER_PROGRAM_SERVICE_H

#include <vector>

#include "../gl_extensions.h"
#include "ishader_service.h"

namespace meow {

struct Program {
	GLint id;
};

class IShaderProgramService {
public:
	virtual ~IShaderProgramService() {};

	virtual Program create(std::vector<Shader*> shaders) = 0;
	virtual void destroy(const Program &program) = 0;
};

} // namespace meow

#endif // SHADER_PROGRAM_SERVICE_H