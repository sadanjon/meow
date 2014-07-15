#ifndef LINE_READER_H 
#define LINE_READER_H

#include <memory>

#include "infra/di.h"
#include "infra/ibuffer_allocator.h"
#include "ifile_system_service.h"
#include "iline_reader.h"

namespace meow {

class LineReader : public ILineReader {
	di::Component<IBufferAllocator> m_bufferAllocator;

	std::shared_ptr<IFile> m_file;
	std::shared_ptr<IBuffer> m_buffer;
	size_t m_readLocation;
	std::shared_ptr<IBuffer> m_singleCharacter;
	std::shared_ptr<std::string> m_line;
	
public:
	LineReader(const std::shared_ptr<IFile> &file);
	Optional<std::string> nextLine() override;

private:
	void reset();
	void readCharacter();
	void appendCharacterToBuffer();
	void setCurrentReadLocationToNullIfEndOfLineOrFile();
	bool isCurrentReadLocationEndOfLineOrFile();
};

} // namespace meow

#endif // LINE_READER_H