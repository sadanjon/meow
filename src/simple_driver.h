#ifndef SIMPLE_DRIVER_H 
#define SIMPLE_DRIVER_H

#include "infra/di.h"
#include "gl/ishader_service.h"
#include "ilog_service.h"
#include "iexception_formatter.h"
#include "imodel_service.h"
#include "idriver_runner.h"
#include "imain_loop_service.h"
#include "iwindow_service.h"

namespace meow {

class SimpleDriver : public IDriver {
	di::Component<IShaderService> m_shaderService;
	di::Component<IModelService> m_modelService;
	di::Component<IMainLoopService> m_mainLoopService;
	di::Component<IExceptionFormatter> m_exceptionFormatter;
	di::Component<ILogService> m_logService;
public:
	int run(int argc, char **argv) override;

private:
	void tryRun();
};

} // namespace meow

#endif // SIMPLE_DRIVER_H