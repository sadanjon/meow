#ifndef MODEL_READER_SERVICE_H 
#define MODEL_READER_SERVICE_H

#include "infra/di.h"
#include "imodel_service.h"

namespace meow {
	
class ModelService : public IModelService {
public:
	std::shared_ptr<Model> create() override;
	std::shared_ptr<Model> createFromOBJFile(const char *path) override;
};

} // namespace meow

#endif // MODEL_READER_SERVICE_H