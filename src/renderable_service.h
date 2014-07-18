#ifndef RENDERABLE_SERVICE_H 
#define RENDERABLE_SERVICE_H

#include "irenderable_service.h"

namespace meow {
	
class RenderableService : public IRenderableService{
public:
	std::shared_ptr<Renderable> create() override;
	std::shared_ptr<Renderable> createFromModel(const Model &model) override;
};

} // namespace meow

#endif // RENDERABLE_SERVICE_H