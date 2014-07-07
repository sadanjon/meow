#ifndef MODEL_READER_SERVICE_H 
#define MODEL_READER_SERVICE_H

#include "di.h"
#include "imodel_service.h"

namespace meow {
	
class ModelService : IModelService {
public:
	Model *create();
	Model *createFromOBJFile(const char *path);

	void destroy(Model *model);

private:
	void destroyMeshes(Model::MeshList *meshes);
	void destroyMesh(Mesh *mesh);
	void destroyVertices(Mesh::VertexList *vertices);
	void destroyIndices(Mesh::IndexList *indices);
	void destroyVertex(Vertex *vertex);
};

} // namespace meow

#endif // MODEL_READER_SERVICE_H