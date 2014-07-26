#include <cstdio>

#include "simple_driver.h"

#include "entities/icamera_service.h"
#include "glm/trigonometric.hpp"

namespace meow {

class SimpleDriverLoopHandler : public ILoopHandler {
	di::Component<IWindowService> m_windowService;
	di::Component<ICameraService> m_cameraService;
	di::Component<IShaderProgramService> m_shaderProgramService;

	bool m_requestQuit;
	std::shared_ptr<IProgram> m_program;
	std::shared_ptr<Renderable> m_renderable;
	std::shared_ptr<ICamera> m_camera;
public:
	SimpleDriverLoopHandler(const std::shared_ptr<IProgram> &program, std::shared_ptr<Renderable> &renderable) :
		m_requestQuit(false),
		m_program(program),
		m_renderable(renderable) {

		m_camera = m_cameraService->create();
		m_cameraService->perspective(*m_camera, PerspectiveParameters{glm::radians(45.0f), 1.0f, 0.1f, 1000.0f});
	}

	void event(const Event &event) override {
		if (event.eventType == EventType::QUIT)
			m_requestQuit = true;
	}

	void update() override {
		m_cameraService->lookAt(*m_camera, LookAtParameters{glm::vec3(0, 0, -10), glm::vec3(0), glm::vec3(0, 1, 0)});
		m_shaderProgramService->use(*m_program);
		m_shaderProgramService->setMatrix4(*m_program, 0, glm::mat4());
		m_shaderProgramService->setMatrix4(*m_program, 1, m_camera->getViewMatrix());
		m_shaderProgramService->setMatrix4(*m_program, 2, m_camera->getProjectionMatrix());
		for (auto &surface : *m_renderable->surfaces) {
			m_shaderProgramService->enableSurfaceAttributes(*m_program, *surface, SurfaceAttributeIDs{ 0 });
			m_shaderProgramService->drawSurface(*m_program, *surface);
			m_shaderProgramService->disableSurfaceAttributes(*m_program, *surface, SurfaceAttributeIDs{ 0 });
		}

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

std::string SimpleDriver::readFile(const std::string &path) {
	auto textReader = m_fileSystemService->getTextReader(path);
	return textReader->read();
}

std::shared_ptr<IShader> SimpleDriver::createVertexShader() {
	auto shader = m_shaderService->create(ShaderType::VERTEX);
	m_shaderService->attachSource(*shader, readFile("../src/shaders/simple.vs"));
	m_shaderService->compile(*shader);
	return shader;
}

std::shared_ptr<IShader> SimpleDriver::createFragmentShader() {
	auto shader = m_shaderService->create(ShaderType::FRAGMENT);
	m_shaderService->attachSource(*shader, readFile("../src/shaders/simple.fs"));
	m_shaderService->compile(*shader);
	return shader;
}

std::shared_ptr<IProgram> SimpleDriver::createProgram() {
	auto vs = createVertexShader();
	auto fs = createFragmentShader();
	auto program = m_shaderProgramService->create();
	m_shaderProgramService->addShader(*program, vs);
	m_shaderProgramService->addShader(*program, fs);
	m_shaderProgramService->link(*program);
	m_shaderProgramService->setUniformIDs(*program, std::vector<std::string>{"model", "view", "proj"});
	m_shaderProgramService->setAttributeIDs(*program, std::vector<std::string>{"position"});
	return program;
}

void SimpleDriver::tryRun() {
	auto program = createProgram();
	auto model = m_modelService->createFromOBJFile("../assets/teapot.obj");
	auto renderable = m_renderableService->createFromModel(*model);

	m_mainLoopService->setHandler(std::make_shared<SimpleDriverLoopHandler>(program, renderable));
	m_mainLoopService->run();
}


} // namespace meow
