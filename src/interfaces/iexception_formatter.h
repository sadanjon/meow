#ifndef IEXCEPTION_FORMATTER_H 
#define IEXCEPTION_FORMATTER_H

#include <exception>

#include "base_exception.h"
#include "buffer.h"

namespace meow {
	
class IExceptionFormatter {
public:
	virtual ~IExceptionFormatter() {}

	virtual void init() throw() = 0;
	virtual void destroy() throw() = 0;

	virtual void format(const BaseException *exception, Buffer *buffer) const throw() = 0;
	virtual void formatSTDException(const std::exception *exception, Buffer *buffer) const throw() = 0;
};

} // namespace meow

#endif // IEXCEPTION_FORMATTER_H