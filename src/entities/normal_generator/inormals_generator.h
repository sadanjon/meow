#ifndef INORMALS_GENERATOR 
#define INORMALS_GENERATOR

#include "imodel_service.h"

namespace meow {
	
class INormalsGenerator {
public:
	virtual ~INormalsGenerator() {}

	virtual void generate(Mesh &mesh, const GenerateNormalsOptions &options) = 0;
};

} // namespace meow

#endif // INORMALS_GENERATOR