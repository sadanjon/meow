#include "logged_shader_service.h"

#include "gl_extensions.h"

namespace meow {

void LoggedShaderService::compile(IShader &shader) {
	ShaderService::compile(shader);
	auto infoLogBuffer = getShaderInfoLog(shader.getID());
	m_logService->info("Shader Info Log:\n%s\n", infoLogBuffer.c_str());
}

std::string LoggedShaderService::getShaderInfoLog(GLint shaderId) {
	std::vector<char> buffer(getShaderInfoLogLength(shaderId));
	glGetShaderInfoLog(shaderId, buffer.size(), nullptr, buffer.data());
	return buffer.data();
}

int LoggedShaderService::getShaderInfoLogLength(GLint shaderId) {
	int infoLogLength;
	glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &infoLogLength);
	return infoLogLength;
}

} // namespace meow
