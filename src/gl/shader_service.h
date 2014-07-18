#ifndef SHADER_H 
#define SHADER_H

#include <string>

#include "ishader_service.h"

namespace meow {

class Shader : public IShader {
	friend class ShaderService;
	
	GLuint m_id;
	ShaderType m_type;
	std::string m_source;
public:
	Shader(ShaderType type);
	~Shader();
	
	GLuint getID() const override;
	ShaderType getType() const override;
	const std::string &getSource() const override;
private:
	GLenum shaderTypeToGLEnum(ShaderType shaderType);
};

class ShaderService : public IShaderService {
public:
	std::shared_ptr<IShader> create(ShaderType shaderType) override;
	void attachSource(IShader &shader, std::string &source) override;
	void compile(IShader &shader) override;

private:
	void checkShaderCompileStatus(GLint shaderId);
	
};

} // namespace meow

#endif // SHADER_H