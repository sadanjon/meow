#include <cstdio>
#include <cstdint>
#include <exception>
#include "SDL.h"

#include "gl_extensions.h"

#include "src/driver.h"

SDL_Window *createSDLWindow();
SDL_GLContext createSDLGLContext(SDL_Window *sdlWindow);

int main(int argc, char **argv) {

	SDL_Window *sdlWindow = createSDLWindow();
	SDL_GLContext glContext = createSDLGLContext(sdlWindow);
	
	meow::Driver driver;
	driver.run(argc, argv);

	SDL_Event event;
	bool running = true;
	while (running) { 
		uint32_t start = SDL_GetTicks();

		while (SDL_PollEvent(&event)) {
			running = event.type != SDL_QUIT;
		}

		SDL_GL_SwapWindow(sdlWindow);

		//printf("%u\n", SDL_GetTicks() - start);
	}


	SDL_GL_DeleteContext(glContext);
	SDL_DestroyWindow(sdlWindow);
	SDL_Quit();
	
	return 0;
}

SDL_Window *createSDLWindow() {
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
SDL_GLContext createSDLGLContext(SDL_Window *sdlWindow) {
	SDL_GL_SetAttribute(SDL_GL_SHARE_WITH_CURRENT_CONTEXT, 1);
	SDL_GLContext context = SDL_GL_CreateContext(sdlWindow);

	if (context == NULL) {
		throw new std::exception("Failed to create SDL context");
		printf("Could not create SDL context: %s", SDL_GetError());
	}

	SDL_GL_SetSwapInterval(1);
	LoadExtensions();

	return context;
}

