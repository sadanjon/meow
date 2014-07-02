#ifndef SHADER_H 
#define SHADER_H

#include "di.h"
#include "interfaces/ishader_service.h"
#include "interfaces/ireader.h"
#include "interfaces/ibuffer_allocator.h"

namespace meow {
using namespace interfaces;

class ShaderService : public IShaderService {
protected:
	di::Component<IReader> m_reader;
	di::Component<IBufferAllocator> m_bufferAllocator;
public:
	Shader create(const char *path, ShaderType::Enum shaderType);
	void destroy(Shader *shader);

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