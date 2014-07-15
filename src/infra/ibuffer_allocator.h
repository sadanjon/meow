#ifndef IBUFFER_ALLOCATOR_H 
#define IBUFFER_ALLOCATOR_H

#include <memory>

namespace meow {

class IBuffer {
public:
	virtual ~IBuffer() {}

	virtual size_t getSize() const = 0;
	virtual size_t getContentSize() const = 0;
	virtual void setContentSize(size_t size) = 0;
	virtual char *get() const = 0;
};

class IBufferAllocator {
public:
	virtual ~IBufferAllocator() {};

	virtual std::shared_ptr<IBuffer> allocate(size_t size) const = 0;
};

} // namespace meow

#endif // IBUFFER_ALLOCATOR_H