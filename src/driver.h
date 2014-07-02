#ifndef DRIVER_H 
#define DRIVER_H

#include "meow_di.h"

namespace meow {
	
class Driver {
	di::Component<IShaderService> m_shaderService;
public:
	virtual ~Driver() {}
	
	void run(int argc, char **argv);
};

} // namespace meow

#endif // DRIVER_H