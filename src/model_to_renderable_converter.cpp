#include "model_to_renderable_converter.h"

#include "SDL_opengl.h"
#include "gl_extensions.h"

namespace meow {
	
std::shared_ptr<Renderable> ModelToRenderableConverter::convert(const Model &model) {
	auto renderable = std::make_shared<Renderable>();
	renderable->surfaces = std::make_shared<SurfaceList>();
	for (auto &mesh : *model.meshes) {
		renderable->surfaces->push_back(meshToSurface(*mesh));
	}
	return renderable;
}

std::shared_ptr<Surface> ModelToRenderableConverter::meshToSurface(const Mesh &mesh) {
	auto surface = std::make_shared<Surface>();
	surface->indexVBO = createIndexVBO(*mesh.indices);
	surface->vertexVBO = createVertexVBO(*mesh.vertices);
	surface->stride = calculateStride(*mesh.vertices->front());
	surface->hasNormals = mesh.vertices->front()->normal.exists();
	surface->hasUVs = mesh.vertices->front()->uv.exists();
	surface->vertexCount = mesh.vertices->size();
	surface->indexCount = mesh.indices->size();
	return surface;
}

std::shared_ptr<IVBO> ModelToRenderableConverter::createIndexVBO(const IndexList &indices) {
	auto vbo = m_vboService->create();
	vbo->setIndexData(indices);
	return vbo;
}

std::shared_ptr<IVBO> ModelToRenderableConverter::createVertexVBO(const VertexList &vertices) {
	auto vbo = m_vboService->create();
	vbo->setVertexData(createVertexData(vertices));
	return vbo;
}

std::vector<float> ModelToRenderableConverter::createVertexData(const VertexList &vertices) {
	std::vector<float> data;
	const auto hasNormals = vertices.front()->normal.exists();
	const auto hasUVs = vertices.front()->uv.exists();
	for (auto vertex : vertices) {
		data.push_back(vertex->position[0]);
		data.push_back(vertex->position[1]);
		data.push_back(vertex->position[2]);

		if (hasNormals) {
			data.push_back(vertex->normal.get()[0]);
			data.push_back(vertex->normal.get()[1]);
			data.push_back(vertex->normal.get()[2]);
		}

		if (hasUVs) {
			data.push_back(vertex->uv.get()[0]);
			data.push_back(vertex->uv.get()[1]);
		}
	}
	return data;
}

int ModelToRenderableConverter::calculateStride(const Vertex &vertex) {
	int stride = sizeof(float) * 3;
	if (vertex.normal.exists())
		stride += sizeof(float) * 3; 
	if (vertex.uv.exists())
		stride += sizeof(float) * 2;
	return stride;
}




} // namespace meow