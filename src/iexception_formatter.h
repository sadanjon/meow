#ifndef IEXCEPTION_FORMATTER_H 
#define IEXCEPTION_FORMATTER_H

#include <exception>
#include <string>

namespace meow {
	
class IExceptionFormatter {
public:
	virtual ~IExceptionFormatter() {}
	virtual std::string format(const std::exception &exception) const throw() = 0;
};

} // namespace meow

#endif // IEXCEPTION_FORMATTER_H