#include "shader_program_service.h"

namespace meow {
	
Program::Program() {
	m_id = glCreateProgram();
}

Program::~Program() {
	glDeleteProgram(m_id);
}

const std::vector<std::shared_ptr<IShader>> &Program::getShaders() const {
	return m_shaders;
}

GLuint Program::getID() const {
	return m_id;
}

std::shared_ptr<IProgram> ShaderProgramService::create() {
	return std::make_shared<Program>();
}

void ShaderProgramService::addShader(IProgram &program, const std::shared_ptr<IShader> &shader) {
	static_cast<Program&>(program).m_shaders.push_back(shader);
	glAttachShader(program.getID(), shader->getID());
}

void ShaderProgramService::link(IProgram &program) {
	glLinkProgram(program.getID());
	checkLinkStatus(program.getID());
}

void ShaderProgramService::checkLinkStatus(GLuint programID) {
	GLint linkStatus;
	glGetProgramiv(programID, GL_LINK_STATUS, &linkStatus);
	if (linkStatus == GL_FALSE)
		throw new IShaderProgramService::LinkProgramFailed();
}

} // namespace meow
