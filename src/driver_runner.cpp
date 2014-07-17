#include "driver_runner.h"

#include <exception>
#include <cstdio>

namespace meow {

int DriverRunner::run(IDriver &driver, int argc, char **argv) {
	SDL_Window *sdlWindow = createSDLWindow();
	SDL_GLContext glContext = createSDLGLContext(sdlWindow);
	
	auto ret = driver.run(argc, argv);

	SDL_GL_DeleteContext(glContext);
	SDL_DestroyWindow(sdlWindow);
	SDL_Quit();

	return ret;
}

SDL_Window *DriverRunner::createSDLWindow() {
	if (SDL_InitSubSystem(SDL_INIT_VIDEO) != 0)
		throw new std::exception("Failed to init SDL");

	SDL_Window *win = SDL_CreateWindow("MEOW",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		800, 600,
		SDL_WINDOW_OPENGL);

	if (win == NULL) {
		printf("Could not create SDL window: %s", SDL_GetError());
		throw new std::exception("Failed to create SDL window");
	}

	return win;
}
SDL_GLContext DriverRunner::createSDLGLContext(SDL_Window *sdlWindow) {
	SDL_GL_SetAttribute(SDL_GL_SHARE_WITH_CURRENT_CONTEXT, 1);
	SDL_GLContext context = SDL_GL_CreateContext(sdlWindow);

	if (context == NULL) {
		throw new std::exception("Failed to create SDL context");
		printf("Could not create SDL context: %s", SDL_GetError());
	}

	SDL_GL_SetSwapInterval(1);
	loadOpenGLExtensions();

	return context;
}

} // namespace meow