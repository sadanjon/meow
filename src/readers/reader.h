#ifndef READER_H 
#define READER_H

#include "di.h"
#include "interfaces/readers/ireader.h"
#include "interfaces/ibuffer_allocator.h"
#include "interfaces/ifile_system_service.h"

namespace meow {

class Reader : public IReader {
	di::Component<IBufferAllocator> m_bufferAllocator;
	di::Component<IFileSystemService> m_fileSystemService;
	
public:
	void read(const char *path, Buffer *buffer);
	Buffer *read(const char *path);

private:
	Buffer *readFileAndAppendNullCharacter(File *file);
	Buffer *createBufferWithFileLengthPlusOne(File *file);
	
};

} // namespace meow

#endif // READER_H