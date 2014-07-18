#include "window_service.h"

#include "gl_extensions.h"

namespace meow {
	
WindowService::WindowService() :
	m_sdlWindow(nullptr) {
}

WindowService::~WindowService() {
	SDL_GL_DeleteContext(m_sdlGLContext);
	SDL_DestroyWindow(m_sdlWindow);
	SDL_Quit();
}

void WindowService::initialize() {
	m_sdlWindow = createSDLWindow();
	m_sdlGLContext = createSDLGLContext();
}

void WindowService::swap() {
	SDL_GL_SwapWindow(m_sdlWindow);
}

SDL_Window *WindowService::createSDLWindow() {
	if (SDL_InitSubSystem(SDL_INIT_VIDEO) != 0)
		throw new IWindowService::FailedToInitializeWindow();

	SDL_Window *win = SDL_CreateWindow("MEOW",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		800, 600,
		SDL_WINDOW_OPENGL);

	if (win == NULL) 
		throw new IWindowService::FailedToInitializeWindow();

	return win;
}

SDL_GLContext WindowService::createSDLGLContext() {
	SDL_GL_SetAttribute(SDL_GL_SHARE_WITH_CURRENT_CONTEXT, 1);
	SDL_GLContext context = SDL_GL_CreateContext(m_sdlWindow);

	if (context == NULL)
		throw new IWindowService::FailedToInitializeWindow();

	SDL_GL_SetSwapInterval(1);
	loadOpenGLExtensions();

	return context;
}

} // namespace meow