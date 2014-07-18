#ifndef IRENDERABLE_SERVICE_H 
#define IRENDERABLE_SERVICE_H

#include "model.h"
#include "renderable.h"

namespace meow {
	
class IRenderableService {
public:
	virtual ~IRenderableService() {}

	virtual std::shared_ptr<Renderable> create() = 0;
	virtual std::shared_ptr<Renderable> createFromModel(const Model &model) = 0;
};

} // namespace meow

#endif // IRENDERABLE_SERVICE_H