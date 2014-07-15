#ifndef EXEPTION_FORMATTER_H 
#define EXEPTION_FORMATTER_H

#include "iexception_formatter.h"

namespace meow {
	
class ExceptionFormatter : public IExceptionFormatter {
public:
	std::string format(const std::exception &exception) const throw() override;
};

} // namespace meow

#endif // EXEPTION_FORMATTER_H