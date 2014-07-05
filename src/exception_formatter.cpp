#include "exception_formatter.h"

#include <cstdio>
#include "snprintf_polyfill.h"
#include <typeinfo>

#include "ifile_system_service.h"

namespace meow {

void baseExceptionFormatter(const BaseException *ex, Buffer *buffer) {
	auto name = typeid(*ex).name();
	buffer->contentSize = snprintf(buffer->buffer, buffer->size, "%s was thrown\n", name);
}

void failedToOpenFileExceptionFormatter(const BaseException *ex, Buffer *buffer) {
	auto cex = static_cast<const IFileSystemService::FailedToOpenFile*>(ex);
	auto name = typeid(*cex).name();
	buffer->contentSize = snprintf(buffer->buffer, buffer->size, "%s was thrown. file: (%s)\n", name, cex->getFileName());
}

void ExceptionFormatter::init() throw() {
}

void ExceptionFormatter::destroy() throw() {

}
	
void ExceptionFormatter::format(const BaseException *exception, Buffer *buffer) const throw() {
	if (typeid(*exception) == typeid(IFileSystemService::FailedToOpenFile))
		failedToOpenFileExceptionFormatter(exception, buffer);
	else 
		baseExceptionFormatter(exception, buffer);
}

void ExceptionFormatter::formatSTDException(const std::exception *exception, Buffer *buffer) const throw() {
	auto name = typeid(*exception).name();
	buffer->contentSize = snprintf(buffer->buffer, buffer->size, "%s was thrown\n", name);	
}

} // namespace meow
