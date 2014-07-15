#include "buffer_allocator.h"

namespace meow {

std::shared_ptr<IBuffer> BufferAllocator::allocate(size_t size) const {
	return std::shared_ptr<IBuffer>(new Buffer(size));
}


} // namespace meow