#ifndef READER_H 
#define READER_H

#include <memory>
#include <string>

#include "infra/di.h"
#include "infra/ibuffer_allocator.h"
#include "ifile_system_service.h"
#include "itext_reader.h"

namespace meow {

class TextReader : public ITextReader {
	di::Component<IBufferAllocator> m_bufferAllocator;
	di::Component<IFileSystemService> m_fileSystemService;

	std::shared_ptr<IFile> m_file;
public:
	TextReader(const std::shared_ptr<IFile> &file);
	std::string read() override;
};

} // namespace meow

#endif // READER_H