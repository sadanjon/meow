#include "obj_reader.h"

#include <boost/regex.hpp>

namespace meow {

Model *OBJReader::read(const char *path) {
	auto buffer = m_bufferAllocator->allocate(512);
	auto file = m_fileSystemService->open(path, "r");

	size_t readCount;
	do {
		readCount = m_fileSystemService->readLine(file, buffer);
		m_logService->info("read line: %s\n", buffer->buffer);
	} while (readCount != 0);

	m_fileSystemService->close(file);
	m_bufferAllocator->destroy(buffer);
	return NULL;
}

} // namespace meow