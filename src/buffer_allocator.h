#ifndef BUFFER_ALLOCATOR_H 
#define BUFFER_ALLOCATOR_H

#include "interfaces/ibuffer_allocator.h"

namespace meow {
	
class BufferAllocator : public IBufferAllocator{
public:
	Buffer *allocate(size_t size);
	void destroy(Buffer *buffer);
};

} // namespace meow

#endif // BUFFER_ALLOCATOR_H
