#include "exception_formatter.h"

#include <typeinfo>

#include "file_system/ifile_system_service.h"

namespace meow {

std::string formatException(const std::exception &ex) {
	auto name = typeid(ex).name();
	return std::string(name) + " was thrown\n";
}

std::string formatFailedToOpenFileException(const IFileSystemService::FailedToOpenFile &ex) {
	return std::string("class IFileSystemService::FailedToOpenFile was thrown. file: ") + ex.getFileName() + "\n";
}

std::string ExceptionFormatter::format(const std::exception &exception) const throw() {
	if (typeid(exception) == typeid(IFileSystemService::FailedToOpenFile))
		return formatFailedToOpenFileException(dynamic_cast<const IFileSystemService::FailedToOpenFile&>(exception));
	return formatException(exception);
}

} // namespace meow
