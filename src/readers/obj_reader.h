#ifndef OBJ_READER_H 
#define OBJ_READER_H

#include "di.h"
#include "interfaces/readers/iobj_reader.h"
#include "interfaces/ifile_system_service.h"
#include "interfaces/ibuffer_allocator.h"
#include "interfaces/ilog_service.h"

namespace meow {

class OBJReader : public IOBJReader {
	di::Component<IFileSystemService> m_fileSystemService;
	di::Component<IBufferAllocator> m_bufferAllocator;
	di::Component<ILogService> m_logService;

public:
	Model *read(const char *path);
};

} // namespace meow

#endif // OBJ_READER_H