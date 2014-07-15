#ifndef FILE_H 
#define FILE_H

#include "SDL.h"

#include "ifile.h"

namespace meow {
	
class File : public IFile {
	friend class FileSystemService;

	SDL_RWops *m_sdlrwops;
public:
	
	File(SDL_RWops *sdlrwops);
	~File();
	size_t read(std::weak_ptr<IBuffer> buffer) override;
	size_t tell() override;
	size_t seek(size_t offset, FileSeekEnum whence) override;
	size_t getSize() override;
	bool isEOF() override;
	void close() override;

protected:
	size_t sdlReadOrThrow(SDL_RWops *sdlrwops, void *ptr, size_t size, size_t maxnum);
	size_t getReadCountOrFileSize(size_t readCount);
	int whenceEnumToRWWhence(FileSeekEnum whenceEnum);

};

} // namespace meow

#endif // FILE_H