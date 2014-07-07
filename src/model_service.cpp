#include "model_service.h"

#include "readers/obj_reader.h"

namespace meow {
	

Model *ModelService::create() {
	auto model = new Model();
	model->meshes = new Model::MeshList();
	return model;
}
Model *ModelService::createFromOBJFile(const char *path) {
	auto model = new Model();
	model->meshes = new Model::MeshList();
	// OBJReader reader;
	// return reader.read(path);
	return model;
}

void ModelService::destroy(Model *model) {
	if (model == nullptr)
		return;
	destroyMeshes(model->meshes);
	delete model;
}

void ModelService::destroyMeshes(Model::MeshList *meshes) {
	if (meshes == nullptr)
		return;
	for (auto mesh : *meshes) 
		destroyMesh(mesh);
	delete meshes;
}

void ModelService::destroyMesh(Mesh *mesh) {
	if (mesh == nullptr)
		return;
	destroyIndices(mesh->indices);
	destroyVertices(mesh->vertices);
	delete mesh;
}

void ModelService::destroyIndices(Mesh::IndexList *indices) {
	if (indices != nullptr) 
		delete indices;
}

void ModelService::destroyVertices(Mesh::VertexList *vertices) {
	if (vertices == nullptr)
		return;
	for (auto vertex : *vertices) 
		destroyVertex(vertex);
	delete vertices;
}

void ModelService::destroyVertex(Vertex *vertex) {
	if (vertex == nullptr)
		return;
	delete[] vertex->position;
	delete[] vertex->normal;
	delete[] vertex->uv;
}

} // namespace meow