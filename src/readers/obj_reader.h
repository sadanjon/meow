#ifndef OBJ_READER_H 
#define OBJ_READER_H


#include "interfaces/readers/iobj_reader.h"

#include "di.h"
#include "interfaces/ifile_system_service.h"
#include "interfaces/ibuffer_allocator.h"
#include "interfaces/ilog_service.h"
#include "vector3.h"

namespace meow {

class OBJReader : public IOBJReader {
public:
	Model *read(const char *path);
};

class StatefullOBJReader {
	di::Component<IFileSystemService> m_fileSystemService;
	di::Component<IBufferAllocator> m_bufferAllocator;
	di::Component<ILogService> m_logService;
public:
	Model *read(const char *path);

private:
	bool tryReadPosition(const char *line, Vector3 *v);
	bool tryReadNormal(const char *line, Vector3 *v);
	bool tryReadUV(const char *line, Vector3 *v);
};



} // namespace meow

#endif // OBJ_READER_H