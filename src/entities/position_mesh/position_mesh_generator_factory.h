#ifndef POSITION_MESH_GENERATOR_FACTORY_H 
#define POSITION_MESH_GENERATOR_FACTORY_H

#include "iposition_mesh_generator_factory.h"

#include "position_mesh_generator.h"

#include <memory>

namespace meow {
	
class PositionMeshGeneratorFactory : public IPositionMeshGeneratorFactory {
public:
	std::shared_ptr<IPositionMeshGenerator> get(const Mesh &mesh) override {
		return std::make_shared<PositionMeshGenerator>(mesh);
	}
	
};

} // namespace meow

#endif // POSITION_MESH_GENERATOR_FACTORY_H