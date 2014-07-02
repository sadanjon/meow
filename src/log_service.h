#ifndef LOG_SERVICE_H 
#define LOG_SERVICE_H

#include "ilog_service.h"

namespace meow {
	
class LogService : public ILogService {
public:

	void setLogPriority(LogPriority::Enum logPriority);

	void info(const char *format, ...);
	void warn(const char *format, ...);
	void error(const char *format, ...);

private:
	LogPriority::Enum m_logPriority;
};

} // namespace meow

#endif // LOG_SERVICE_H