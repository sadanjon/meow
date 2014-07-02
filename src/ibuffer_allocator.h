#ifndef IBUFFER_ALLOCATOR_H 
#define IBUFFER_ALLOCATOR_H

#include "buffer.h"

namespace meow {

class IBufferAllocator
{
public:
	virtual ~IBufferAllocator() {};

	virtual Buffer *allocate(size_t size) = 0;
	virtual void destroy(Buffer *buffer) = 0;
};

} // namespace meow

#endif // IBUFFER_ALLOCATOR_H