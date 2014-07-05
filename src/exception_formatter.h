#ifndef EXEPTION_FORMATTER_H 
#define EXEPTION_FORMATTER_H

#include "iexception_formatter.h"

#include <unordered_map>

namespace meow {
	
class ExceptionFormatter : public IExceptionFormatter {
public:
	void init() throw();
	void destroy() throw();
	void format(const BaseException *exception, Buffer *buffer) const throw();
	void formatSTDException(const std::exception *exception, Buffer *buffer) const throw();

private:
	typedef void (*FormatFunction)(const BaseException *exception, Buffer *buffer);
	std::unordered_map<const char*, FormatFunction> m_formatters;
};

} // namespace meow

#endif // EXEPTION_FORMATTER_H