#ifndef MODEL_READER_SERVICE_H 
#define MODEL_READER_SERVICE_H

#include "infra/di.h"
#include "imodel_service.h"
#include "entities/normal_generator/inormals_generator.h"

namespace meow {
	
class ModelService : public IModelService {
	di::Component<INormalsGenerator> m_normalsGenerator;
public:
	std::shared_ptr<Model> create() override;
	std::shared_ptr<Model> createFromOBJFile(const char *path) override;
	void generateNormals(Model &model, const GenerateNormalsOptions &options) override;
};

} // namespace meow

#endif // MODEL_READER_SERVICE_H