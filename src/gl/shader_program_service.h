#ifndef SHADER_PROGRAM_SERVICE_H 
#define SHADER_PROGRAM_SERVICE_H

#include <vector>

#include "ishader_program_service.h"

namespace meow {
	
class Program : public IProgram {
	friend class ShaderProgramService;
	GLuint m_id;
	std::vector<std::shared_ptr<IShader>> m_shaders;
public:
	Program();
	~Program();
	
	const std::vector<std::shared_ptr<IShader>> &getShaders() const override;
	GLuint getID() const override;
};

class ShaderProgramService : public IShaderProgramService {
public:
	std::shared_ptr<IProgram> create() override;
	void addShader(IProgram &program, const std::shared_ptr<IShader> &shader) override;
	void link(IProgram &program) override;

private:
	void checkLinkStatus(GLuint programID);
};

} // namespace meow

#endif // SHADER_PROGRAM_SERVICE_H