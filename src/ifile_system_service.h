#ifndef IFILE_SERVICE_H 
#define IFILE_SERVICE_H

#include <cstdint>
#include <cstdio>
#include <exception>

#include "buffer.h"

namespace meow {

struct File;

struct SeekWhence {
	enum Enum {
		SET,
		CUR,
		END
	};
};

class IFileSystemService {
public:
	virtual ~IFileSystemService() {}

	virtual File *open(const char *path, const char *mode) = 0;
	virtual size_t read(File *file, Buffer *buffer) = 0;
	virtual int64_t tell(File *file) = 0;
	virtual int64_t seek(File *file, int64_t offset, SeekWhence::Enum whence) = 0;
	virtual void close(File *file) = 0;

	class FailedToOpenFile : public std::exception {};
	class FailedToReadFile : public std::exception {};
	class InvalidWhenceEnum : public std::exception {};
};

} // namespace meow

#endif // IFILE_SERVICE_H