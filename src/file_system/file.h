#ifndef FILE_H 
#define FILE_H

#include "SDL.h"

#include "ifile.h"
#include "infra/optional.h"

namespace meow {
	
class File : public IFile {
	friend class FileSystemService;

	SDL_RWops *m_sdlrwops;
	Optional<size_t> m_fileSize;
public:
	
	File(SDL_RWops *sdlrwops);
	File(const File &) = delete;
	File &operator=(File) = delete;
	~File();

	size_t read(std::vector<char> &buffer) override;
	size_t tell() override;
	size_t seek(size_t offset, FileSeekEnum whence) override;
	size_t getSize() override;
	bool isEOF() override;
	void close() override;

protected:
	size_t sdlReadOrThrow(SDL_RWops *sdlrwops, void *ptr, size_t amount);
	size_t getReadCountOrFileSize(size_t readCount);
	int whenceEnumToRWWhence(FileSeekEnum whenceEnum);
	size_t calculateFileSize();
	size_t getFileSize();

};

} // namespace meow

#endif // FILE_H