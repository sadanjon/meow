#ifndef IREADER_H 
#define IREADER_H

namespace meow {
namespace interfaces {
	
struct Buffer;
	
class IReader
{
public:
	virtual ~IReader() {}
	virtual void read(const char *path, Buffer *buffer) = 0;
	virtual Buffer *read(const char *path) = 0;
};

} // namespace interfaces
} // namespace meow

#endif // IREADER_H