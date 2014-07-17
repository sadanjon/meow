#ifndef ISHADER_H 
#define ISHADER_H

#include <exception>
#include <memory>

#include "SDL_opengl.h"


namespace meow {

enum class ShaderType {
	VERTEX,
	FRAGMENT
};

class IShader {
public:
	virtual ~IShader() {}

	virtual GLuint getID() = 0;
	virtual ShaderType getType() = 0;
};
	
class IShaderService {
public:
	virtual ~IShaderService() {}
	
	virtual std::shared_ptr<IShader> create(const char *path, ShaderType shaderType) = 0;

	class InvalidShaderTypeEnum : public std::exception {};
	class ShaderCompilationFailed : public std::exception {};
};

} // namespace meow

#endif // ISHADER_H