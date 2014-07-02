#include "buffer_allocator.h"

namespace meow {

Buffer *BufferAllocator::allocate(size_t size) {
	Buffer *b = new Buffer();
	b->buffer = new char[size];
	b->size = size;
	b->contentSize = 0;
	return b;
}

void BufferAllocator::destroy(Buffer *buffer) {
	delete[] buffer->buffer;
	delete buffer;
}

} // namespace meow