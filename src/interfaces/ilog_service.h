#ifndef ILOG_SERVICE_H 
#define ILOG_SERVICE_H

namespace meow {
namespace interfaces {

struct LogPriority {
	enum Enum {
		INFO,
		WARN,
		ERR
	};
};
	
class ILogService {
public:
	virtual ~ILogService() {}

	virtual void setLogPriority(LogPriority::Enum logPriority) = 0;
	
	virtual void info(const char *format, ...) = 0;
	virtual void warn(const char *format, ...) = 0;
	virtual void error(const char *format, ...) = 0;
};
	
} // namespace interfaces
} // namespace meow


#endif // ILOG_SERVICE_H