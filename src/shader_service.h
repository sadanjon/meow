#ifndef SHADER_H 
#define SHADER_H

#include "di.h"
#include "ishader_service.h"
#include "ireader.h"
#include "ibuffer_allocator.h"

namespace meow {
	
class ShaderService : public IShaderService {
protected:
	di::Component<IReader> m_reader;
	di::Component<IBufferAllocator> m_bufferAllocator;
public:
	Shader create(const char *path, ShaderType::Enum shaderType);
	void destroy(const Shader &shader);

protected:
	virtual void compileShader(GLint shaderId);

private:
	void setShaderSource(GLint shaderId, const char *path);
	void checkShaderCompileStatus(GLint shaderId);
	Shader createShaderFromId(GLint shaderId);
	GLenum shaderTypeToGLEnum(ShaderType::Enum shaderType);
};

} // namespace meow

#endif // SHADER_H