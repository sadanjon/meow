#ifndef IMODEL_SERVICE_H 
#define IMODEL_SERVICE_H

#include <memory>

#include "model.h"

namespace meow {
	
struct GenerateNormalsOptions {
	bool faceNormals;
	bool clockwiseFaces;
};

class IModelService {
public:
	virtual ~IModelService() {}

	virtual std::shared_ptr<Model> create() = 0;
	virtual std::shared_ptr<Model> createFromOBJFile(const char *path) = 0;
	virtual void generateNormals(Model &model, const GenerateNormalsOptions &options) = 0;
};

} // namespace meow

#endif // IMODEL_SERVICE_H