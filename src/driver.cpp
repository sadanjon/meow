#include "driver.h"

#include <cstdio>

namespace meow {
	
void Driver::run(int argc, char **argv) {
	auto shader = m_shaderService->create("../src/shaders/simple.vs", ShaderType::VERTEX);
	printf("read: %d\n", shader.id);
	m_shaderService->destroy(&shader);
}


} // namespace meow
