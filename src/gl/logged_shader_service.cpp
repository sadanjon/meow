#include "logged_shader_service.h"

#include "../gl_extensions.h"

namespace meow {

void LoggedShaderService::compileShader(GLint shaderId) {
	ShaderService::compileShader(shaderId);
	auto infoLogBuffer = getShaderInfoLog(shaderId);
	m_logService->info("Shader Info Log:\n%s\n", infoLogBuffer->get());
}

std::shared_ptr<IBuffer> LoggedShaderService::getShaderInfoLog(GLint shaderId) {
	auto buffer = m_bufferAllocator->allocate(getShaderInfoLogLength(shaderId));
	glGetShaderInfoLog(shaderId, buffer->getSize(), nullptr, buffer->get());
	return buffer;
}

int LoggedShaderService::getShaderInfoLogLength(GLint shaderId) {
	int infoLogLength;
	glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &infoLogLength);
	return infoLogLength;
}

} // namespace meow
