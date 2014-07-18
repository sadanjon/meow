#ifndef MODEL_TO_RENDERABLE_CONVERTER_H 
#define MODEL_TO_RENDERABLE_CONVERTER_H

#include "infra/di.h"
#include "gl/ivbo_service.h"
#include "model.h"
#include "renderable.h"

namespace meow {
	
class ModelToRenderableConverter {
	di::Component<IVBOService> m_vboService;
public:
	std::shared_ptr<Renderable> convert(const Model &model);

private:
	std::shared_ptr<Surface> meshToSurface(const Mesh &mesh);
	std::shared_ptr<IVBO> createIndexVBO(const IndexList &indices);
	std::shared_ptr<IVBO> createVertexVBO(const VertexList &vertices);
	std::vector<float> createVertexData(const VertexList &vertices);
	int calculateStride(const Vertex &vertex);
};

} // namespace meow

#endif // MODEL_TO_RENDERABLE_CONVERTER_H