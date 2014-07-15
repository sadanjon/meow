#include "SDL.h"

#include "infra/di.h"
#include "file_system_service.h"
#include "line_reader.h"
#include "text_reader.h"
#include "file.h"

namespace meow {

std::shared_ptr<IFile> FileSystemService::open(const std::string &path, const std::string &mode) {
	return std::make_shared<File>(createSDLRWopsOrThrow(path.c_str(), mode.c_str()));
}

std::shared_ptr<ILineReader> FileSystemService::getLineReader(const std::string &path) {
	return std::make_shared<LineReader>(std::make_shared<File>(createSDLRWopsOrThrow(path.c_str(), "r")));
}

std::shared_ptr<ITextReader> FileSystemService::getTextReader(const std::string &path) {
	return std::make_shared<TextReader>(std::make_shared<File>(createSDLRWopsOrThrow(path.c_str(), "r")));
}

SDL_RWops *FileSystemService::createSDLRWopsOrThrow(const char *path, const char *mode) {
	auto ops = SDL_RWFromFile(path, mode);
	if (ops == NULL)
		throw new IFileSystemService::FailedToOpenFile(path);
	return ops;
}

} // namespace meow
