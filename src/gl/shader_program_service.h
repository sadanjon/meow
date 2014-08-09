#ifndef SHADER_PROGRAM_SERVICE_H 
#define SHADER_PROGRAM_SERVICE_H

#include <vector>

#include "infra/di.h"
#include "ishader_program_service.h"
#include "ivbo_service.h"

namespace meow {
	
class Program : public IProgram {
	friend class ShaderProgramService;
	GLuint m_id;
	std::vector<std::shared_ptr<IShader>> m_shaders;
	std::vector<GLint> m_uniformIDMap;
	std::vector<GLint> m_attributeIDMap;
public:
	Program();
	Program(const Program &) = delete;
	Program &operator=(Program) = delete;
	~Program();



	const std::vector<std::shared_ptr<IShader>> &getShaders() const override;
	GLuint getID() const override;
};

class ShaderProgramService : public IShaderProgramService {
	di::Component<IVBOService> m_vboService;
public:
	std::shared_ptr<IProgram> create() override;
	void addShader(IProgram &program, const std::shared_ptr<IShader> &shader) override;
	void link(IProgram &program) override;
	void use(IProgram &program) override;
	void setUniformIDs(IProgram &program, const std::vector<std::string> &uniforms) override;
	void setAttributeIDs(IProgram &program, const std::vector<std::string> &attributes) override;
	void setMatrix4(IProgram &program, int uniformID, const glm::mat4 &matrix4) override;
	void setVector3(IProgram &program, int uniformID, const glm::vec3 &vector3) override;
	void enableSurfaceAttributes(IProgram &program, const Surface &surface, const SurfaceAttributeIDs& attributeIDs) override;
	void disableSurfaceAttributes(IProgram &program, const Surface &surface, const SurfaceAttributeIDs& attributeIDs) override;
	void drawSurface(IProgram &program, const Surface &surface) override;

protected:
	virtual void checkLinkStatus(GLuint programID);
private:
	void setVertexPositionAttrib(Program &program, const Surface &surface, const SurfaceAttributeIDs& attributeIDs);
	void setVertexNormalAttribIfExists(Program &program, const Surface &surface, const SurfaceAttributeIDs& attributeIDs);
	void setVertexUVAttribIfExists(Program &program, const Surface &surface, const SurfaceAttributeIDs& attributeIDs);
	void setVertexAttribPointer(GLuint id, GLint size, const Surface &surface, int byteOffset);
};

} // namespace meow

#endif // SHADER_PROGRAM_SERVICE_H