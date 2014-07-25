#ifndef ICAMERA_SERVICE_H 
#define ICAMERA_SERVICE_H

#include <memory>

#include "glm/vec3.hpp"

#include "icamera.h"

namespace meow {

struct LookAtParameters {
	glm::vec3 position;
	glm::vec3 target;
	glm::vec3 up;
};

struct PerspectiveParameters {
	float fov; // in radians
	float aspect;
	float nearPlane;
	float farPlane;
};
	
class ICameraService {
public:
	virtual ~ICameraService() {}
	
	virtual std::shared_ptr<ICamera> create() = 0;
	virtual void perspective(ICamera &camera, const PerspectiveParameters &perspectiveParameters) = 0;
	virtual void lookAt(ICamera &camera, const LookAtParameters &lookAtParameters) = 0;
};

} // namespace meow

#endif // ICAMERA_SERVICE_H