#include "main_loop_service.h"

#include "SDL.h"

namespace meow {


DefaultLoopHandler::DefaultLoopHandler() : m_requestQuit(false) {
}

void DefaultLoopHandler::event(const SDL_Event &event) {
	if (event.type == SDL_QUIT)
		m_requestQuit = true;
}

void DefaultLoopHandler::update() {
}

bool DefaultLoopHandler::isQuitRequested() {
	return m_requestQuit;
}

MainLoopService::MainLoopService() : 
	m_running(true),
	m_loopHandler(std::make_shared<DefaultLoopHandler>()) {
}
	
void MainLoopService::run() {
	SDL_Event event;
	m_running = true;
	while (m_running && !m_loopHandler->isQuitRequested()) {
		while (SDL_PollEvent(&event))
			m_loopHandler->event(event);
		m_loopHandler->update();
	}
}

void MainLoopService::setHandler(const std::shared_ptr<ILoopHandler> &handler) {
	m_loopHandler = handler;
}

void MainLoopService::requestToQuit() {
	m_running = false;
}

} // namespace meow