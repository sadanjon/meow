#include "file_system_service.h"

#include "SDL.h"

namespace meow {

struct File {
	SDL_RWops *sdlrwops;
};

class LineReader {
	FileSystemService *m_fileSystemService;
	File *m_file;
	Buffer *m_buffer;
	size_t m_readCount;
	size_t m_readLocation;
	char m_singleCharacter;
	bool m_isEndOfFile;
public:
	LineReader(FileSystemService *fileSystemService, File *file, Buffer *buffer);
	size_t readLine();

private:
	void readCharacterOrThrow();
	void appendCharacterToBuffer();
	void setCurrentReadLocationToNullIfEndOfLineOrFile();
	bool isCurrentReadLocationEndOfLineOrFile();
};


static SDL_RWops *createSDLRWopsOrThrow(const char *path, const char *mode) {
	auto ops = SDL_RWFromFile(path, mode);
	if (ops == NULL)
		throw new IFileSystemService::FailedToOpenFile(path);
	return ops;
}

static int whenceEnumToRWWhence(SeekWhence::Enum whenceEnum) {
	switch(whenceEnum) {
	case SeekWhence::SET:
		return RW_SEEK_SET;
	case SeekWhence::CUR:
		return RW_SEEK_CUR;
	case SeekWhence::END:
		return RW_SEEK_END;
	default:
		throw new IFileSystemService::InvalidWhenceEnum();
	}
}
	
File *FileSystemService::open(const char *path, const char *mode) {
	auto sdlrwops = createSDLRWopsOrThrow(path, mode);
	auto file = new File();
	file->sdlrwops = sdlrwops;
	return file;
}

static size_t getReadCountOrFileSize(size_t readCount, File *file) {
	if (readCount == 0)
		return (size_t) SDL_RWtell(file->sdlrwops);
	else
		return readCount;
}

size_t FileSystemService::read(File *file, Buffer *buffer) {
	auto readCount = sdlReadOrThrow(file, buffer->buffer, 1, buffer->size);
	buffer->contentSize = getReadCountOrFileSize(readCount, file);
	return readCount;
}

size_t FileSystemService::readLine(File *file, Buffer *buffer) {
	LineReader lineReader(this, file, buffer);
	return lineReader.readLine();
}

size_t FileSystemService::tell(File *file) {
	return static_cast<size_t>(SDL_RWtell(file->sdlrwops));
}

size_t FileSystemService::seek(File *file, size_t offset, SeekWhence::Enum whence) {
	return static_cast<size_t>(SDL_RWseek(file->sdlrwops, offset, whenceEnumToRWWhence(whence)));
}

void FileSystemService::close(File *file) {
	SDL_RWclose(file->sdlrwops);
	delete file;
}

size_t FileSystemService::sdlReadOrThrow(File *file, void *ptr, size_t size, size_t maxnum) {
	auto readCount = SDL_RWread(file->sdlrwops, ptr, size, maxnum);
	if (*SDL_GetError() != '\0')
		throw new IFileSystemService::FailedToReadFile();
	return readCount;
}



LineReader::LineReader(FileSystemService *fileSystemService, File *file, Buffer *buffer) :
		m_fileSystemService(fileSystemService),
		m_file(file),
		m_buffer(buffer),
		m_readCount(0),
		m_readLocation(0),
		m_singleCharacter('C'),
		m_isEndOfFile(false) {
			
}

size_t LineReader::readLine() {
	m_buffer->contentSize = 0;
	for (m_readLocation = 0; m_readLocation < m_buffer->size && !isCurrentReadLocationEndOfLineOrFile(); ++m_readLocation) {
		readCharacterOrThrow();
		setCurrentReadLocationToNullIfEndOfLineOrFile();
		if (!isCurrentReadLocationEndOfLineOrFile())
			appendCharacterToBuffer();
	}
	return m_buffer->contentSize;	
}

void LineReader::readCharacterOrThrow() {
	auto readCount = SDL_RWread(m_file->sdlrwops, &m_singleCharacter, 1, 1);
	if (*SDL_GetError() != '\0')
		throw new IFileSystemService::FailedToReadFile();
	if (readCount == 0)
		m_isEndOfFile = true;
}

void LineReader::setCurrentReadLocationToNullIfEndOfLineOrFile() {
	if (isCurrentReadLocationEndOfLineOrFile())
		m_buffer->buffer[m_readLocation] = '\0';
}

bool LineReader::isCurrentReadLocationEndOfLineOrFile() {
	return m_singleCharacter == '\n' || m_isEndOfFile;
}

void LineReader::appendCharacterToBuffer() {
	m_buffer->buffer[m_readLocation] = m_singleCharacter;
	m_buffer->contentSize += 1;
}

} // namespace meow
