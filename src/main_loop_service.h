#ifndef MAIN_LOOP_SERVICE_H 
#define MAIN_LOOP_SERVICE_H

#include "SDL.h"

#include "imain_loop_service.h"

namespace meow {

class DefaultLoopHandler : public ILoopHandler {
	bool m_requestQuit;
public:
	DefaultLoopHandler();
	void event(const Event &event) override;
	void update() override;
	bool isQuitRequested() override;
};
	
class MainLoopService : public IMainLoopService {
	std::shared_ptr<ILoopHandler> m_loopHandler;
	bool m_running;
public:
	MainLoopService();

	void run() override;
	void setHandler(const std::shared_ptr<ILoopHandler> &handler) override;
	void requestToQuit() override;

private:
	Event sdlEventToEvent(SDL_Event &sdlEvent);
};

} // namespace meow

#endif // MAIN_LOOP_SERVICE_H