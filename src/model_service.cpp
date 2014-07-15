#include "model_service.h"

#include "readers/obj_reader/obj_reader.h"

namespace meow {

std::shared_ptr<Model> ModelService::create() {
	return std::make_shared<Model>();
}
std::shared_ptr<Model> ModelService::createFromOBJFile(const char *path) {
	auto objReader = std::make_unique<OBJReader>(path);
	return std::shared_ptr<Model>(objReader->read());
}

} // namespace meow