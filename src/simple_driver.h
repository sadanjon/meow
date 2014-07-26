#ifndef SIMPLE_DRIVER_H 
#define SIMPLE_DRIVER_H

#include "infra/di.h"
#include "gl/ishader_service.h"
#include "gl/ishader_program_service.h"
#include "file_system/ifile_system_service.h"
#include "ilog_service.h"
#include "iexception_formatter.h"
#include "imodel_service.h"
#include "idriver_runner.h"
#include "imain_loop_service.h"
#include "iwindow_service.h"
#include "irenderable_service.h"

namespace meow {

class SimpleDriver : public IDriver {
	di::Component<IShaderService> m_shaderService;
	di::Component<IShaderProgramService> m_shaderProgramService;
	di::Component<IFileSystemService> m_fileSystemService;
	di::Component<IModelService> m_modelService;
	di::Component<IRenderableService> m_renderableService;
	di::Component<IMainLoopService> m_mainLoopService;
	di::Component<IWindowService> m_windowService;
	di::Component<IExceptionFormatter> m_exceptionFormatter;
	di::Component<ILogService> m_logService;
public:
	int run(int argc, char **argv) override;

private:
	void tryRun();
	std::string readFile(const std::string &path);
	std::shared_ptr<IShader> createVertexShader();
	std::shared_ptr<IShader> createFragmentShader();
	std::shared_ptr<IProgram> createProgram();
};

} // namespace meow

#endif // SIMPLE_DRIVER_H