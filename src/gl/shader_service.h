#ifndef SHADER_H 
#define SHADER_H

#include "infra/di.h"
#include "ishader_service.h"
#include "file_system/ifile_system_service.h"

namespace meow {

class ShaderService : public IShaderService {
protected:
	di::Component<IFileSystemService> m_fileSystemService;
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