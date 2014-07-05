#ifndef BASE_EXCEPTION_H 
#define BASE_EXCEPTION_H

#include <cstdio>
#include <cstring>

namespace meow {
	
class BaseException {
public:
	virtual ~BaseException() {}
};

} // namespace meow

#endif // BASE_EXCEPTION_H