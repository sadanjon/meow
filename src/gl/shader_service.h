#ifndef SHADER_H 
#define SHADER_H

#include "infra/di.h"
#include "ishader_service.h"
#include "file_system/ifile_system_service.h"

namespace meow {

class Shader : public IShader {
	GLuint m_id;
	ShaderType m_type;
public:
	Shader(GLuint id, ShaderType type);
	~Shader();

	GLuint getID();
	ShaderType getType();
};

class ShaderService : public IShaderService {
protected:
	di::Component<IFileSystemService> m_fileSystemService;
public:
	std::shared_ptr<IShader> create(const char *path, ShaderType shaderType) override;

protected:
	virtual void compileShader(GLint shaderId);

private:
	void setShaderSource(GLint shaderId, const char *path);
	void checkShaderCompileStatus(GLint shaderId);
	GLenum shaderTypeToGLEnum(ShaderType shaderType);
};

} // namespace meow

#endif // SHADER_H