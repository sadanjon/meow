#include "main_loop_service.h"

#include "SDL.h"

namespace meow {


DefaultLoopHandler::DefaultLoopHandler() : m_requestQuit(false) {
}

void DefaultLoopHandler::event(const Event &event) {
	if (event.eventType == EventType::QUIT)
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
			m_loopHandler->event(sdlEventToEvent(event));
		m_loopHandler->update();
	}
}

void MainLoopService::setHandler(const std::shared_ptr<ILoopHandler> &handler) {
	m_loopHandler = handler;
}

void MainLoopService::requestToQuit() {
	m_running = false;
}

Event MainLoopService::sdlEventToEvent(SDL_Event &sdlEvent) {
	if (sdlEvent.type == SDL_QUIT) {
		return Event {EventType::QUIT};
	} else {
		return Event{ EventType::UNKNOWN };
	}
}

} // namespace meow