#ifndef IITERATOR_H 
#define IITERATOR_H

namespace meow {
	
template<typename T>
class IIterator {
public:
	virtual ~IIterator() {}
	
	virtual bool hasNext() = 0;
	virtual T next() = 0;
};

} // namespace meow

#endif // IITERATOR_H