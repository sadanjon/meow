#ifndef FILE_SYSTEM_SERVICE_H 
#define FILE_SYSTEM_SERVICE_H

#include "interfaces/ifile_system_service.h"

namespace meow {
using namespace interfaces;
	
class FileSystemService : public IFileSystemService {
public:
	File *open(const char *path, const char *mode);
	size_t read(File *file, Buffer *buffer);
	size_t tell(File *file);
	size_t seek(File *file, size_t offset, SeekWhence::Enum whence);
	void close(File *file);
	
};

} // namespace meow

#endif // FILE_SYSTEM_SERVICE_H