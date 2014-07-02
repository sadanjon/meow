#ifndef IOBJ_READER_H 
#define IOBJ_READER_H

#include "model.h"

namespace meow {

class IOBJReader {
public:
	virtual ~IOBJReader() {}
	virtual Model *read(const char *path) = 0;
};

} // namespace meow

#endif // IOBJ_READER_H
