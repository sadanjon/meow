#include "renderable_service.h"

#include "model_to_renderable_converter.h"

namespace meow {

std::shared_ptr<Renderable> RenderableService::create() {
	auto r = std::make_shared<Renderable>();
	r->surfaces = std::make_shared<SurfaceList>();
	return r;
}

std::shared_ptr<Renderable> RenderableService::createFromModel(const Model &model) {
	auto converter = std::make_unique<ModelToRenderableConverter>();
	return converter->convert(model);
}

} // namespace meow