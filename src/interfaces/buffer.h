#ifndef BUFFER_H 
#define BUFFER_H

namespace meow {

struct Buffer {
	char *buffer;
	size_t size;
	size_t contentSize;
};

} // namespace meow

#endif // BUFFER_H