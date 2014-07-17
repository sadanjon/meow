#ifndef DRIVER_RUNNER_H 
#define DRIVER_RUNNER_H

#include <memory>

#include "idriver_runner.h"
#include "SDL.h"
#include "gl_extensions.h"

namespace meow {
	
class DriverRunner : public IDriverRunner {
	SDL_Window *m_sdlWindow;
	SDL_GLContext m_sdlGLContext;
public:
	DriverRunner();
	~DriverRunner();
	int run(IDriver &driver, int argc, char **argv) override;

private:
	SDL_Window *createSDLWindow();
	SDL_GLContext createSDLGLContext();
};

} // namespace meow

#endif // DRIVER_RUNNER_H