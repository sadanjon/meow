#include <cstdio>

#include "simple_driver.h"

namespace meow {

int SimpleDriver::run(int argc, char **argv) {
	try {
		tryRun();
	} catch (std::exception &e) {
		auto s = m_exceptionFormatter->format(e);
		m_logService->error("%s", s.c_str());
	}
	return 0;
}
	
void SimpleDriver::tryRun() {
	// auto shader = m_shaderService->create("../src/shaders/simple.vs", ShaderType::VERTEX);
	// m_shaderService->destroy(&shader);

	auto model = m_modelService->createFromOBJFile("../assets/twotri.obj");
}


} // namespace meow
