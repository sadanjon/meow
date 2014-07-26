#ifndef ISHADER_PROGRAM_SERVICE_H 
#define ISHADER_PROGRAM_SERVICE_H

#include <vector>
#include <exception>
#include <string>

#include "glm/matrix.hpp"

#include "ishader_service.h"
#include "gl_extensions.h"
#include "renderable.h"
#include "infra/optional.h"

namespace meow {

class IProgram {
public:
	virtual ~IProgram() {}
	
	virtual const std::vector<std::shared_ptr<IShader>> &getShaders() const = 0;
	virtual GLuint getID() const = 0;
};

struct SurfaceAttributeIDs {
	int position;
	Optional<int> normal;
	Optional<int> uv;
};

class IShaderProgramService {
public:
	virtual ~IShaderProgramService() {};

	virtual std::shared_ptr<IProgram> create() = 0;
	virtual void addShader(IProgram &program, const std::shared_ptr<IShader> &shader) = 0;
	virtual void link(IProgram &program) = 0;
	virtual void use(IProgram &program) = 0;
	virtual void setUniformIDs(IProgram &program, const std::vector<std::string> &uniforms) = 0;
	virtual void setAttributeIDs(IProgram &program, const std::vector<std::string> &attributes) = 0;
	virtual void setMatrix4(IProgram &program, int uniformID, const glm::mat4 &matrix4) = 0;
	virtual void enableSurfaceAttributes(IProgram &program, const Surface &surface, const SurfaceAttributeIDs& attributeIDs) = 0;
	virtual void disableSurfaceAttributes(IProgram &program, const Surface &surface, const SurfaceAttributeIDs& attributeIDs) = 0;
	virtual void drawSurface(IProgram &program, const Surface &surface) = 0;

	class LinkProgramFailed : public std::exception {};
};


} // namespace meow

#endif // ISHADER_PROGRAM_SERVICE_H