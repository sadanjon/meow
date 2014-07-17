#ifndef DRIVER_RUNNER_H 
#define DRIVER_RUNNER_H

#include "idriver_runner.h"
#include "SDL.h"
#include "gl_extensions.h"

namespace meow {
	
class DriverRunner : public IDriverRunner {
public:
	int run(IDriver &driver, int argc, char **argv) override;

private:
	SDL_Window *createSDLWindow();
	SDL_GLContext createSDLGLContext(SDL_Window *sdlWindow);
};

} // namespace meow

#endif // DRIVER_RUNNER_H