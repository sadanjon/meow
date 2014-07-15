#ifndef ISHADER_H 
#define ISHADER_H

#include <exception>

#include "SDL_opengl.h"


namespace meow {
	
struct Shader {
	GLuint id;
};

struct ShaderType {
	enum Enum {
		VERTEX,
		FRAGMENT
	};
};
	
class IShaderService {
public:
	virtual ~IShaderService() {}
	
	virtual Shader create(const char *path, ShaderType::Enum shaderType) = 0;
	virtual void destroy(Shader *shader) = 0;

	class InvalidShaderTypeEnum : public std::exception {};
	class ShaderCompilationFailed : public std::exception {};
};

} // namespace meow

#endif // ISHADER_H