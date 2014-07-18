#ifndef ISHADER_PROGRAM_SERVICE_H 
#define ISHADER_PROGRAM_SERVICE_H

#include <vector>
#include <exception>

#include "ishader_service.h"

#include "../gl_extensions.h"

namespace meow {

class IProgram {
public:
	virtual ~IProgram() {}
	
	virtual const std::vector<std::shared_ptr<IShader>> &getShaders() const = 0;
	virtual GLuint getID() const = 0;
};

class IShaderProgramService {
public:
	virtual ~IShaderProgramService() {};

	virtual std::shared_ptr<IProgram> create() = 0;
	virtual void addShader(IProgram &program, const std::shared_ptr<IShader> &shader) = 0;
	virtual void link(IProgram &program) = 0;

	class LinkProgramFailed : public std::exception {};
};


} // namespace meow

#endif // ISHADER_PROGRAM_SERVICE_H