#ifndef IBUFFER_ALLOCATOR_H 
#define IBUFFER_ALLOCATOR_H

#include "buffer.h"

namespace meow {
namespace interfaces {

class IBufferAllocator
{
public:
	virtual ~IBufferAllocator() {};

	virtual Buffer *allocate(size_t size) = 0;
	virtual void destroy(Buffer *buffer) = 0;
};

} // namespace interfaces
} // namespace meow

#endif // IBUFFER_ALLOCATOR_H