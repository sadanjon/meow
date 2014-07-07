#ifndef DRIVER_H 
#define DRIVER_H

#include "di.h"
#include "ishader_service.h"
#include "ibuffer_allocator.h"
#include "ilog_service.h"
#include "iexception_formatter.h"
#include "imodel_service.h"
#include "idriver.h"


namespace meow {
	
class Driver : public IDriver {
	di::Component<IShaderService> m_shaderService;
	di::Component<IBufferAllocator> m_bufferAllocator;
	di::Component<IModelService> m_modelService;
	di::Component<IExceptionFormatter> m_exceptionFormatter;
	di::Component<ILogService> m_logService;
public:
	void run(int argc, char **argv);

private:
	void tryRun(int argc, char **argv);
};

} // namespace meow

#endif // DRIVER_H