#include <cstdio>
#include <exception>

#include "shader_service.h"

#include "../gl_extensions.h"


namespace meow {

Shader ShaderService::create(const char *path, ShaderType::Enum shaderType) {
	auto id = glCreateShader(shaderTypeToGLEnum(shaderType));
	setShaderSource(id, path);
	compileShader(id);
	checkShaderCompileStatus(id);
	return createShaderFromId(id);
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

Shader ShaderService::createShaderFromId(GLint shaderId) {
	Shader shader;
	shader.id = shaderId;
	return shader;
}



void ShaderService::destroy(Shader *shader) {
	glDeleteShader(shader->id);
	shader->id = 0;
}

GLenum ShaderService::shaderTypeToGLEnum(ShaderType::Enum shaderType) {
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