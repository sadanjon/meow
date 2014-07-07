#include <cstdio>

#include "driver.h"

namespace meow {

void Driver::run(int argc, char **argv) {
	auto buffer = m_bufferAllocator->allocate(1024);
	m_exceptionFormatter->init();

	try {
		tryRun(argc, argv);
	} catch (BaseException *e) {
		m_exceptionFormatter->format(e, buffer);
		m_logService->error("%s", buffer->buffer);
	} catch (std::exception *e) {
		m_exceptionFormatter->formatSTDException(e, buffer);
		m_logService->error("%s", buffer->buffer);
	}

}
	
void Driver::tryRun(int argc, char **argv) {
	auto shader = m_shaderService->create("../src/shaders/simple.vs", ShaderType::VERTEX);
	
	m_modelService->createFromOBJFile("../assets/twotri.obj");

	m_shaderService->destroy(&shader);
}


} // namespace meow
