#include <cstdio>

#include "driver.h"

namespace meow {

void Driver::run(int argc, char **argv) {
	try {
		tryRun(argc, argv);
	} catch (std::exception &e) {
		auto s = m_exceptionFormatter->format(e);
		m_logService->error("%s", s.c_str());
	}

}
	
void Driver::tryRun(int argc, char **argv) {
	// auto shader = m_shaderService->create("../src/shaders/simple.vs", ShaderType::VERTEX);
	// m_shaderService->destroy(&shader);

	auto model = m_modelService->createFromOBJFile("../assets/twotri.obj");
}


} // namespace meow
