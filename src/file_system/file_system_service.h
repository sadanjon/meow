#ifndef FILE_SYSTEM_SERVICE_H 
#define FILE_SYSTEM_SERVICE_H

#include <memory>

#include "SDL.h"

#include "ifile_system_service.h"

namespace meow {
	
class FileSystemService : public IFileSystemService {
public:
	std::shared_ptr<IFile> open(const std::string &path, const std::string &mode) override;
	std::shared_ptr<ILineReader> getLineReader(const std::string &path) override;
	std::shared_ptr<ITextReader> getTextReader(const std::string &path) override;
private:
	SDL_RWops *createSDLRWopsOrThrow(const char *path, const char *mode);
};

} // namespace meow

#endif // FILE_SYSTEM_SERVICE_H