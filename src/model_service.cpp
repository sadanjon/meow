#include "model_service.h"

#include <memory>

#include "glm/geometric.hpp"

#include "readers/obj_reader/obj_reader.h"

namespace meow {

std::shared_ptr<Model> ModelService::create() {
	return std::make_shared<Model>();
}

std::shared_ptr<Model> ModelService::createFromOBJFile(const char *path) {
	auto objReader = std::make_unique<OBJReader>(path);
	return std::shared_ptr<Model>(objReader->read());
}

void ModelService::generateNormals(Model &model, const GenerateNormalsOptions &options) {
	for (auto &mesh : *model.meshes) {
		m_normalsGenerator->generate(*mesh, options);
	}
}

} // namespace meow
