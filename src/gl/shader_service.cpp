#include <cstdio>
#include <exception>

#include "shader_service.h"

#include "../gl_extensions.h"


namespace meow {

Shader::Shader(ShaderType type) :
	m_type(type) {
	m_id = glCreateShader(shaderTypeToGLEnum(type));
}

Shader::~Shader() {
	glDeleteShader(m_id);
}

const std::string &Shader::getSource() const {
	return m_source;
}

GLuint Shader::getID() const {
	return m_id;
}

ShaderType Shader::getType() const {
	return m_type;
}

GLenum Shader::shaderTypeToGLEnum(ShaderType shaderType) {
	switch (shaderType) {
	case ShaderType::VERTEX:
		return GL_VERTEX_SHADER;
	case ShaderType::FRAGMENT:
		return GL_FRAGMENT_SHADER;
	default:
		throw new IShaderService::InvalidShaderTypeEnum();
	}
}

std::shared_ptr<IShader> ShaderService::create(ShaderType shaderType) {
	return std::make_shared<Shader>(shaderType);
}

void ShaderService::attachSource(IShader &shader, std::string &source) {
	auto c = source.c_str();
	glShaderSource(shader.getID(), 1, (const char **)&c, nullptr);
	static_cast<Shader&>(shader).m_source = source;
}

void ShaderService::compile(IShader &shader) {
	glCompileShader(shader.getID());
	checkShaderCompileStatus(shader.getID());
}

void ShaderService::checkShaderCompileStatus(GLint shaderId) {
	GLint compileStatus;
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &compileStatus);
	if (compileStatus == GL_FALSE)
		throw new IShaderService::ShaderCompilationFailed();
}




} // namespace meow