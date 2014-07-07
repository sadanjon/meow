#ifndef IMODEL_SERVICE_H 
#define IMODEL_SERVICE_H

#include "model.h"

namespace meow {
	
class IModelService {
public:
	virtual ~IModelService() {}

	virtual Model *create() = 0;
	virtual Model *createFromOBJFile(const char *path) = 0;
	virtual void destroy(Model *model) = 0;
};

} // namespace meow

#endif // IMODEL_SERVICE_H