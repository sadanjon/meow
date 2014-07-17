#ifndef IFILE_H 
#define IFILE_H

#include <memory>
#include <exception>
#include <vector>
#include <array>

namespace meow {

enum class FileSeekEnum {
	SET,
	CUR,
	END
};

class IFile {
public:
	virtual ~IFile() {}
	virtual size_t read(std::vector<char> &buffer) = 0;
	virtual size_t tell() = 0;
	virtual size_t seek(size_t offset, FileSeekEnum whence) = 0;
	virtual size_t getSize() = 0;
	virtual bool isEOF() = 0;
	virtual void close() = 0;

	class FailedToReadFile : public std::exception {};
	class InvalidWhenceEnum : public std::exception {};
};

} // namespace meow

#endif // IFILE_H