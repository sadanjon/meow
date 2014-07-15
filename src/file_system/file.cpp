#include "file.h"

namespace meow {

File::File(SDL_RWops *sdlrwops) :
	m_sdlrwops(sdlrwops) {
}

File::~File() {
	close();
}

size_t File::read(std::weak_ptr<IBuffer> buffer) {
	auto b = buffer.lock();
	auto readCount = sdlReadOrThrow(m_sdlrwops, b->get(), 1, b->getSize());
	b->setContentSize(getReadCountOrFileSize(readCount));
	return readCount;
}

size_t File::tell() {
	return static_cast<size_t>(SDL_RWtell(m_sdlrwops));
}

size_t File::seek(size_t offset, FileSeekEnum whence) {
	return static_cast<size_t>(SDL_RWseek(m_sdlrwops, offset, whenceEnumToRWWhence(whence)));
}

size_t File::getSize() {
	auto c = SDL_RWtell(m_sdlrwops);
	auto e = SDL_RWseek(m_sdlrwops, 0, RW_SEEK_END);
	SDL_RWseek(m_sdlrwops, c, RW_SEEK_SET);
	return e;
}

bool File::isEOF() {
	auto c = SDL_RWtell(m_sdlrwops);
	auto e = SDL_RWseek(m_sdlrwops, 0, RW_SEEK_END);
	SDL_RWseek(m_sdlrwops, c, RW_SEEK_SET);
	return c == e;
}

void File::close() {
	if (!m_sdlrwops)
		return;
	SDL_RWclose(m_sdlrwops);
	m_sdlrwops = nullptr;
}

size_t File::sdlReadOrThrow(SDL_RWops *sdlrwops, void *ptr, size_t size, size_t maxnum) {
	auto readCount = SDL_RWread(sdlrwops, ptr, size, maxnum);
	if (*SDL_GetError() != '\0')
		throw new IFile::FailedToReadFile();
	return readCount;
}

size_t File::getReadCountOrFileSize(size_t readCount) {
	if (readCount == 0)
		return (size_t)SDL_RWtell(m_sdlrwops);
	else
		return readCount;
}

int File::whenceEnumToRWWhence(FileSeekEnum whenceEnum) {
	switch (whenceEnum) {
	case FileSeekEnum::SET:
		return RW_SEEK_SET;
	case FileSeekEnum::CUR:
		return RW_SEEK_CUR;
	case FileSeekEnum::END:
		return RW_SEEK_END;
	default:
		throw new IFile::InvalidWhenceEnum();
	}
}

} // namespace meow