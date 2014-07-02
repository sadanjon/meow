#include "reader.h"

#include <exception>

#include "SDL.h"

#include "interfaces/ibuffer_allocator.h"

namespace meow {
	
void Reader::read(const char *path, Buffer *buffer) {
	auto file = m_fileSystemService->open(path, "r");
	m_fileSystemService->read(file, buffer);
	m_fileSystemService->close(file);
}

Buffer *Reader::read(const char *path) {
	auto file = m_fileSystemService->open(path, "r");
	auto buffer = readFileAndAppendNullCharacter(file);
	m_fileSystemService->close(file);
	return buffer;
}

Buffer *Reader::readFileAndAppendNullCharacter(File *file) {
	auto buffer = createBufferWithFileLengthPlusOne(file);
	m_fileSystemService->read(file, buffer);
	buffer->buffer[buffer->size - 1] = '\0';
	return buffer;
}

Buffer *Reader::createBufferWithFileLengthPlusOne(File *file) {
	auto length = m_fileSystemService->seek(file, 0, SeekWhence::END);
	m_fileSystemService->seek(file, 0, SeekWhence::SET);
	return m_bufferAllocator->allocate(length + 1);
}



} // namespace meow