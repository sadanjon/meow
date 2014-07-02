#ifndef IREADER_H 
#define IREADER_H

namespace meow {
	
struct Buffer;
	
class IReader
{
public:
	virtual ~IReader() {}
	virtual void read(const char *path, Buffer *buffer) = 0;
	virtual Buffer *read(const char *path) = 0;
};

} // namespace meow

#endif // IREADER_H