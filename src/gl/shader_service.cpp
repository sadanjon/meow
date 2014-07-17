#include <cstdio>
#include <exception>

#include "shader_service.h"

#include "../gl_extensions.h"


namespace meow {


Shader::Shader(GLuint id, ShaderType type) :
	m_id(id),
	m_type(type) {
}

Shader::~Shader() {
	glDeleteShader(m_id);
}

GLuint Shader::getID() {
	return m_id;
}

ShaderType Shader::getType() {
	return m_type;
}

std::shared_ptr<IShader> ShaderService::create(const char *path, ShaderType shaderType) {
	auto id = glCreateShader(shaderTypeToGLEnum(shaderType));
	setShaderSource(id, path);
	compileShader(id);
	checkShaderCompileStatus(id);
	return std::make_shared<Shader>(id, shaderType);
}

void ShaderService::setShaderSource(GLint shaderId, const char *path) {
	auto reader = m_fileSystemService->getTextReader(path);
	auto buffer = reader->read();
	auto c = buffer.c_str();
	glShaderSource(shaderId, 1, (const char **)&c, nullptr);
}

void ShaderService::compileShader(GLint shaderId) {
	glCompileShader(shaderId);
}

void ShaderService::checkShaderCompileStatus(GLint shaderId) {
	GLint compileStatus;
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &compileStatus);
	if (compileStatus == GL_FALSE)
		throw new IShaderService::ShaderCompilationFailed();
}

GLenum ShaderService::shaderTypeToGLEnum(ShaderType shaderType) {
	switch (shaderType) {
	case ShaderType::VERTEX:
		return GL_VERTEX_SHADER;
	case ShaderType::FRAGMENT:
		return GL_FRAGMENT_SHADER;
	default:
		throw new IShaderService::InvalidShaderTypeEnum();
	}
}


} // namespace meow