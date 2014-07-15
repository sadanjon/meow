#ifndef IFILE_SYSTEM_SERVICE_H 
#define IFILE_SYSTEM_SERVICE_H

#include <cstdint>
#include <cstdio>
#include <memory>
#include <string>

#include "infra/ibuffer_allocator.h"
#include "infra/optional.h"
#include "ifile.h"
#include "iline_reader.h"
#include "itext_reader.h"

namespace meow {

class IFileSystemService {
public:
	virtual ~IFileSystemService() {}

	virtual std::shared_ptr<IFile> open(const std::string &path, const std::string &mode) = 0;
	virtual std::shared_ptr<ILineReader> getLineReader(const std::string &path) = 0;
	virtual std::shared_ptr<ITextReader> getTextReader(const std::string &path) = 0;

	class FailedToOpenFile : public std::exception {
		const char *m_fileName;
	public:
		FailedToOpenFile(const char *fileName) : m_fileName(fileName) {}
		const char *getFileName() const {
			return m_fileName;
		}
	};

};

} // namespace meow

#endif // IFILE_SYSTEM_SERVICE_H