#ifndef IOBJ_READER_H 
#define IOBJ_READER_H

#include <memory>
#include <exception>

#include "model.h"

namespace meow {
	
class IOBJReader {
public:
	virtual ~IOBJReader() {}
	virtual std::shared_ptr<Model> read() = 0;

	class IllFormedOBJFile : public std::exception {};	
};

} // namespace meow

#endif // IOBJ_READER_H