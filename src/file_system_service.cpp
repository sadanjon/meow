#include "file_system_service.h"

#include "SDL.h"

namespace meow {

struct File {
	SDL_RWops *sdlrwops;
};

static SDL_RWops *createSDLRWopsOrThrow(const char *path, const char *mode) {
	auto ops = SDL_RWFromFile(path, mode);
	if (ops == NULL)
		throw new IFileSystemService::FailedToOpenFile();
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
	auto readCount = SDL_RWread(file->sdlrwops, buffer->buffer, 1, buffer->size);
	if (*SDL_GetError() != '\0')
		throw new IFileSystemService::FailedToReadFile();
	buffer->contentSize = getReadCountOrFileSize(readCount, file);
	return readCount;
}

int64_t FileSystemService::tell(File *file) {
	return SDL_RWtell(file->sdlrwops);
}

int64_t FileSystemService::seek(File *file, int64_t offset, SeekWhence::Enum whence) {
	return SDL_RWseek(file->sdlrwops, offset, whenceEnumToRWWhence(whence));
}

void FileSystemService::close(File *file) {
	SDL_RWclose(file->sdlrwops);
	delete file;
}



} // namespace meow
