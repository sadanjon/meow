#include <cstdio>

#include "simple_driver.h"

namespace meow {

class SimpleDriverLoopHandler : public ILoopHandler {
	di::Component<IWindowService> m_windowService;
	bool m_requestQuit;
public:
	SimpleDriverLoopHandler() : m_requestQuit(false) {}
	void event(const Event &event) override {
		if (event.eventType == EventType::QUIT)
			m_requestQuit = true;
	}

	void update() override {
		m_windowService->swap();
	}

	bool isQuitRequested() override {
		return m_requestQuit;
	}
};

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
	//auto model = m_modelService->createFromOBJFile("../assets/twotri.obj");

	m_mainLoopService->setHandler(std::make_shared<SimpleDriverLoopHandler>());
	m_mainLoopService->run();
}


} // namespace meow
