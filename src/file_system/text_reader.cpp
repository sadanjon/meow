#include "text_reader.h"

#include <exception>

#include "SDL.h"

namespace meow {

TextReader::TextReader(const std::shared_ptr<IFile> &file) : m_file(file) {
}

std::string TextReader::read() {
	std::vector<char> buffer(m_file->getSize());
	m_file->read(buffer);
	buffer[buffer.size() - 1] = '\0';
	return buffer.data();
}

} // namespace meow