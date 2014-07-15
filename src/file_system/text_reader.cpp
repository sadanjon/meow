#include "text_reader.h"

#include <exception>

#include "SDL.h"

#include "infra/ibuffer_allocator.h"

namespace meow {

TextReader::TextReader(const std::shared_ptr<IFile> &file) : m_file(file) {
}

std::string TextReader::read() {
	auto buffer = m_bufferAllocator->allocate(m_file->getSize() + 1);
	m_file->read(buffer);
	buffer->get()[buffer->getSize() - 1] = '\0';
	return buffer->get();
}

} // namespace meow