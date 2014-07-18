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

	virtual const std::string &getSource() const = 0;
	virtual GLuint getID() const = 0;
	virtual ShaderType getType() const = 0;
};
	
class IShaderService {
public:
	virtual ~IShaderService() {}
	
	virtual std::shared_ptr<IShader> create(ShaderType shaderType) = 0;
	virtual void attachSource(IShader &shader, std::string &source) = 0;
	virtual void compile(IShader &shader) = 0;

	class InvalidShaderTypeEnum : public std::exception {};
	class ShaderCompilationFailed : public std::exception {};
};

} // namespace meow

#endif // ISHADER_H