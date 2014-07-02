#ifndef BUFFER_H 
#define BUFFER_H

namespace meow {
namespace interfaces {

struct Buffer {
	char *buffer;
	size_t size;
	size_t contentSize;
};

} // namespace interfaces
} // namespace meow

#endif // BUFFER_H