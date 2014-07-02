#ifndef FILE_SYSTEM_SERVICE_H 
#define FILE_SYSTEM_SERVICE_H

#include "ifile_system_service.h"

namespace meow {
	
class FileSystemService : public IFileSystemService {
public:
	File *open(const char *path, const char *mode);
	size_t read(File *file, Buffer *buffer);
	int64_t tell(File *file);
	int64_t seek(File *file, int64_t offset, SeekWhence::Enum whence);
	void close(File *file);
	
};

} // namespace meow

#endif // FILE_SYSTEM_SERVICE_H