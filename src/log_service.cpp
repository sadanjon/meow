#include "log_service.h"

#include <cstdio>
#include <cstdarg>

#include "SDL.h"

#define BUFFER_LENGTH 4096

static char infoBuffer[BUFFER_LENGTH];
static char warnBuffer[BUFFER_LENGTH];
static char errorBuffer[BUFFER_LENGTH];

#define FORMAT_STRING(buffer, format)\
	va_list args;\
	va_start(args, format);\
	vsprintf(buffer, format, args);\
	va_end(args);\

namespace meow {

	void LogService::setLogPriority(LogPriority::Enum logPriority) {
		m_logPriority = logPriority;
	}

	void LogService::info(const char *format, ...) {
		if (m_logPriority > LogPriority::INFO)
			return;
		FORMAT_STRING(infoBuffer, format);
		SDL_Log("%s", infoBuffer);
	}

	void LogService::warn(const char *format, ...) {
		if (m_logPriority > LogPriority::WARN)
			return;
		FORMAT_STRING(warnBuffer, format);
		SDL_Log("%s", warnBuffer);
	}

	void LogService::error(const char *format, ...) {
		if (m_logPriority > LogPriority::ERR)
			return;
		FORMAT_STRING(errorBuffer, format);
		SDL_Log("%s", errorBuffer);
	}

} // namespace meow

