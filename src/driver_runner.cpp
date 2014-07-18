#include "driver_runner.h"

#include <exception>
#include <cstdio>

namespace meow {

int DriverRunner::run(IDriver &driver, int argc, char **argv) {
	m_windowService->initialize();
	return driver.run(argc, argv);
}

} // namespace meow