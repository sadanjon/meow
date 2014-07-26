#include "shader_program_service.h"

#include "glm/gtc/type_ptr.hpp"

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

void ShaderProgramService::use(IProgram &program) {
	glUseProgram(program.getID());
}

void ShaderProgramService::setUniformIDs(IProgram &program, const std::vector<std::string> &uniforms) {
	auto &p = static_cast<Program&>(program);
	for (auto &uniform : uniforms) {
		p.m_uniformIDMap.push_back(glGetUniformLocation(p.getID(), uniform.c_str()));
	}
}

void ShaderProgramService::setAttributeIDs(IProgram &program, const std::vector<std::string> &attributes) {
	auto &p = static_cast<Program&>(program);
	for (auto &attribute : attributes) {
		p.m_attributeIDMap.push_back(glGetAttribLocation(p.getID(), attribute.c_str()));
	}
}

void ShaderProgramService::setMatrix4(IProgram &program, int uniformID, const glm::mat4 &matrix4) {
	auto &p = static_cast<Program&>(program);
	glUniformMatrix4fv(p.m_uniformIDMap[uniformID], 1, GL_FALSE, glm::value_ptr(matrix4));
}

void ShaderProgramService::enableSurfaceAttributes(IProgram &program, const Surface &surface, const SurfaceAttributeIDs& attributeIDs) {
	auto &p = static_cast<Program&>(program);
	m_vboService->bindVertexVBO(*surface.vertexVBO);
	setVertexPositionAttrib(p, surface, attributeIDs);
	setVertexNormalAttribIfExists(p, surface, attributeIDs);
	setVertexUVAttribIfExists(p, surface, attributeIDs);
	m_vboService->unbindVertexVBO();
}

void ShaderProgramService::setVertexPositionAttrib(Program &program, const Surface &surface, const SurfaceAttributeIDs& attributeIDs) {
	glEnableVertexAttribArray(program.m_attributeIDMap[attributeIDs.position]);
	setVertexAttribPointer(program.m_attributeIDMap[attributeIDs.position], 3, surface, 0);
}

void ShaderProgramService::setVertexNormalAttribIfExists(Program &program, const Surface &surface, const SurfaceAttributeIDs& attributeIDs) {
	if (!attributeIDs.normal.exists() || !surface.hasNormals)
		return;
	glEnableVertexAttribArray(program.m_attributeIDMap[attributeIDs.normal.get()]);
	setVertexAttribPointer(program.m_attributeIDMap[attributeIDs.normal.get()], 3, surface, sizeof(float)* 3);
}

void ShaderProgramService::setVertexUVAttribIfExists(Program &program, const Surface &surface, const SurfaceAttributeIDs& attributeIDs) {
	if (!attributeIDs.uv.exists() || !surface.hasUVs)
		return;
	glEnableVertexAttribArray(program.m_attributeIDMap[attributeIDs.uv.get()]);
	setVertexAttribPointer(program.m_attributeIDMap[attributeIDs.uv.get()], 2, surface, sizeof(float)* 5);
}

void ShaderProgramService::setVertexAttribPointer(GLuint id, GLint size, const Surface &surface, int byteOffset) {
	glVertexAttribPointer(id, size, GL_FLOAT, GL_FALSE, surface.stride, (void*)(byteOffset));
}

void ShaderProgramService::disableSurfaceAttributes(IProgram &program, const Surface &surface, const SurfaceAttributeIDs& attributeIDs) {
	auto &p = static_cast<Program&>(program);
	glDisableVertexAttribArray(p.m_attributeIDMap[attributeIDs.position]);
	if (surface.hasNormals && attributeIDs.normal.exists())
		glDisableVertexAttribArray(p.m_attributeIDMap[attributeIDs.normal.get()]);
	if (surface.hasUVs && attributeIDs.uv.exists())
		glDisableVertexAttribArray(p.m_attributeIDMap[attributeIDs.uv.get()]);
}

void ShaderProgramService::checkLinkStatus(GLuint programID) {
	GLint linkStatus;
	glGetProgramiv(programID, GL_LINK_STATUS, &linkStatus);
	if (linkStatus == GL_FALSE)
		throw new IShaderProgramService::LinkProgramFailed();
}

void ShaderProgramService::drawSurface(IProgram &program, const Surface &surface) {
	m_vboService->bindIndexVBO(*surface.indexVBO);
	glDrawElements(GL_TRIANGLES, surface.indexCount, GL_UNSIGNED_INT, (void*)(0));
	m_vboService->unbindIndexVBO();
}

} // namespace meow
