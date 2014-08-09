#include "line_reader.h"

namespace meow {
	
LineReader::LineReader(const std::shared_ptr<IFile> &file) :
	m_file(file),
	m_buffer(512, 0),
	m_readLocation(0),
	m_singleCharacter(1, 'C'),
	m_isEOF(false) {
}

Optional<std::string> LineReader::nextLine() {
	m_readLocation = 0;
	m_singleCharacter[0] = 'C';
	for (m_readLocation = 0; m_readLocation < m_buffer.size() && !isCurrentReadLocationEndOfLineOrFile(); ++m_readLocation) {
		readCharacter();
		setCurrentReadLocationToNullIfEndOfLineOrFile();
		if (!isCurrentReadLocationEndOfLineOrFile())
			appendCharacterToBuffer();
	}
	if (m_readLocation > 0)
		return m_buffer.data();
	else
		return createOptional<std::string>();
}

void LineReader::readCharacter() {
	m_isEOF = m_file->read(m_singleCharacter) == 0;
}

void LineReader::appendCharacterToBuffer() {
	m_buffer[m_readLocation] = m_singleCharacter[0];
}

void LineReader::setCurrentReadLocationToNullIfEndOfLineOrFile() {
	if (isCurrentReadLocationEndOfLineOrFile())
		m_buffer[m_readLocation] = '\0';
}

bool LineReader::isCurrentReadLocationEndOfLineOrFile() {
	return m_singleCharacter[0] == '\n' || m_isEOF;
}


} // namespace meow

