#ifndef WINDOW_SERVICE_H 
#define WINDOW_SERVICE_H

#include "SDL.h"

#include "iwindow_service.h"

namespace meow {
	
class WindowService : public IWindowService {
	SDL_Window *m_sdlWindow;
	SDL_GLContext m_sdlGLContext;
public:
	WindowService();
	~WindowService();

	void initialize() override;
	void swap() override;

private:
	SDL_Window *createSDLWindow();
	SDL_GLContext createSDLGLContext();
};

} // namespace meow

#endif // WINDOW_SERVICE_H