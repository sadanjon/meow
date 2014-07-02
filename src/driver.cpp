#include <cstdio>

#include "driver.h"

namespace meow {
	
void Driver::run(int argc, char **argv) {
	auto shader = m_shaderService->create("../src/shaders/simple.vs", ShaderType::VERTEX);
	
	m_objReader->read("../assets/twotri.obj");

	m_shaderService->destroy(&shader);
}


} // namespace meow
