#include "normals_generator.h"

#include "face_normals_generator.h"
#include "vertex_normals_generator.h"

namespace meow {
	
void NormalsGenerator::generate(Mesh &mesh, const GenerateNormalsOptions &options) {
	if (options.faceNormals)
		generateFaceNormals(mesh, options);
	else
		generateVertexNormals(mesh, options);

	m_logService->info("vertices count: %d", mesh.vertices->size());

	auto c = 0;
	for (auto &v : *mesh.vertices) {
		if (v->normal.exists())
			c += 1;
	}
	m_logService->info("normals count: %d", c);

}

void NormalsGenerator::generateFaceNormals(Mesh &mesh, const GenerateNormalsOptions &options) {
	auto faceNormalsGenerator = std::make_unique<FaceNormalsGenerator>(mesh, options.clockwiseFaces);
	faceNormalsGenerator->generate();
}

void NormalsGenerator::generateVertexNormals(Mesh &mesh, const GenerateNormalsOptions &options) {
	auto vertexNormalsGenerator = std::make_unique<VertexNormalsGenerator>(mesh, options.clockwiseFaces);
	vertexNormalsGenerator->generate();
}

} // namespace meow