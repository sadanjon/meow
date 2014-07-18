#ifndef DRIVER_RUNNER_H 
#define DRIVER_RUNNER_H

#include <memory>

#include "infra/di.h"
#include "iwindow_service.h"
#include "idriver_runner.h"
#include "SDL.h"
#include "gl_extensions.h"

namespace meow {
	
class DriverRunner : public IDriverRunner {
	di::Component<IWindowService> m_windowService;
public:
	int run(IDriver &driver, int argc, char **argv) override;
};

} // namespace meow

#endif // DRIVER_RUNNER_H