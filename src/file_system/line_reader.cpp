#include "line_reader.h"

namespace meow {
	
LineReader::LineReader(const std::shared_ptr<IFile> &file) :
	m_file(file),
	m_buffer(nullptr),
	m_readLocation(0),
	m_singleCharacter(nullptr) {
	m_buffer = m_bufferAllocator->allocate(512);
	m_singleCharacter = m_bufferAllocator->allocate(1);
}

Optional<std::string> LineReader::nextLine() {
	m_readLocation = 0;
	m_singleCharacter->get()[0] = 'A';
	m_buffer->setContentSize(0);
	for (m_readLocation = 0; m_readLocation < m_buffer->getSize() && !isCurrentReadLocationEndOfLineOrFile(); ++m_readLocation) {
		readCharacter();
		setCurrentReadLocationToNullIfEndOfLineOrFile();
		if (!isCurrentReadLocationEndOfLineOrFile())
			appendCharacterToBuffer();
	}
	if (m_buffer->getContentSize() > 0)
		return m_buffer->get();
	else
		return createOptional<std::string>();
}

void LineReader::readCharacter() {
	m_file->read(m_singleCharacter);
}

void LineReader::appendCharacterToBuffer() {
	m_buffer->get()[m_readLocation] = m_singleCharacter->get()[0];
	m_buffer->setContentSize(m_buffer->getContentSize() + 1);
}

void LineReader::setCurrentReadLocationToNullIfEndOfLineOrFile() {
	if (isCurrentReadLocationEndOfLineOrFile())
		m_buffer->get()[m_readLocation] = '\0';
}

bool LineReader::isCurrentReadLocationEndOfLineOrFile() {
	return m_singleCharacter->get()[0] == '\n' || m_file->isEOF();
}


} // namespace meow

