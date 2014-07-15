#ifndef BUFFER_ALLOCATOR_H 
#define BUFFER_ALLOCATOR_H

#include "ibuffer_allocator.h"

namespace meow {

class Buffer : public IBuffer {
	friend class BufferAllocator;
	size_t m_size;
	size_t m_contentSize;
	char *m_buffer;

	Buffer(size_t size) :
		m_size(size),
		m_contentSize(0),
		m_buffer(new char[size]) {
	}
public:
	~Buffer() {
		delete[] m_buffer;
	}

	size_t getSize() const override {
		return m_size;
	}

	size_t getContentSize() const  override{
		return m_contentSize;
	}

	void setContentSize(size_t size) override {
		m_contentSize = size;
	}

	char *get() const override {
		return m_buffer;
	}
};

class BufferAllocator : public IBufferAllocator {
public:
	std::shared_ptr<IBuffer> allocate(size_t size) const override;
};

} // namespace meow

#endif // BUFFER_ALLOCATOR_H
