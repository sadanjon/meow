#ifndef IPOSITION_MESH_GENERATOR_H 
#define IPOSITION_MESH_GENERATOR_H

#include <memory>

#include "model.h"

namespace meow {

class IPositionMesh {
public:
	IPositionMesh() {}
	virtual ~IPositionMesh() {}

	IPositionMesh(const IPositionMesh&) = delete;
	IPositionMesh &operator=(const IPositionMesh &) = delete;

	virtual const IndexList &getOriginalVertexIndicesAt(IndexType index) const = 0;
	virtual std::shared_ptr<Mesh> getMesh() const = 0;

	class VertexNotFound : std::exception {};
};
	
class IPositionMeshGenerator {
public:
	IPositionMeshGenerator() {}
	virtual ~IPositionMeshGenerator() {}

	IPositionMeshGenerator(const IPositionMeshGenerator&) = delete;
	IPositionMeshGenerator &operator=(const IPositionMeshGenerator&) = delete;

	virtual std::shared_ptr<IPositionMesh> generate() = 0;
};


class IPositionMeshGeneratorFactory {
public:
	IPositionMeshGeneratorFactory() {}
	virtual ~IPositionMeshGeneratorFactory() {}

	IPositionMeshGeneratorFactory(const IPositionMeshGeneratorFactory&) = delete;
	IPositionMeshGeneratorFactory &operator=(const IPositionMeshGeneratorFactory&) = delete;

	virtual std::shared_ptr<IPositionMeshGenerator> get(const Mesh &mesh) = 0;

};

} // namespace meow

#endif // IPOSITION_MESH_GENERATOR_H