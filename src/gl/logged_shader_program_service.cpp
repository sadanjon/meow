#include "logged_shader_program_service.h"

namespace meow {
	
void LoggedShaderProgramService::checkLinkStatus(GLuint programID) {
	auto infoLog = getProgramInfoLog(programID);
	m_logService->info("Program Info Log:\n%s\n", infoLog.c_str());
	ShaderProgramService::checkLinkStatus(programID);
}

std::string LoggedShaderProgramService::getProgramInfoLog(GLint programID) {
	std::vector<char> buffer(getProgramInfoLogLength(programID));
	glGetProgramInfoLog(programID, buffer.size(), nullptr, buffer.data());
	return buffer.data();
}

int LoggedShaderProgramService::getProgramInfoLogLength(GLint programID) {
	int infoLogLength;
	glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
	return infoLogLength;
}

} // namespace meow