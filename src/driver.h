#ifndef DRIVER_H 
#define DRIVER_H

#include "idriver.h"
#include "iexception_formatter.h"

#include "meow_di.h"

namespace meow {
	
class Driver : public IDriver {
	di::Component<IShaderService> m_shaderService;
	di::Component<IOBJReader> m_objReader;
	di::Component<IBufferAllocator> m_bufferAllocator;
	di::Component<IExceptionFormatter> m_exceptionFormatter;
public:
	void run(int argc, char **argv);

private:
	void tryRun(int argc, char **argv);
};

} // namespace meow

#endif // DRIVER_H