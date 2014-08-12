#ifndef NORMALS_GENERATOR_H 
#define NORMALS_GENERATOR_H

#include "inormals_generator.h"

namespace meow {
	
class NormalsGenerator : INormalsGenerator {
public:
	void generate(Mesh &mesh, const GenerateNormalsOptions &options) override;

private:
	void generateFaceNormals(Mesh &mesh, const GenerateNormalsOptions &options);
	void generateVertexNormals(Mesh &mesh, const GenerateNormalsOptions &options);
};

} // namespace meow

#endif // NORMALS_GENERATOR_H