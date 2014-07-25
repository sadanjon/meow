#include "camera_service.h"

#include "glm/gtc/matrix_transform.hpp"

#include "camera.h"

namespace meow {

std::shared_ptr<ICamera> CameraService::create() {
	return std::make_shared<Camera>();
}

void CameraService::perspective(ICamera &camera, const PerspectiveParameters &perspectiveParameters) {
	auto c = static_cast<Camera&>(camera);
	c.m_projection = glm::perspective(perspectiveParameters.fov, perspectiveParameters.aspect, perspectiveParameters.nearPlane, perspectiveParameters.farPlane);
}

void CameraService::lookAt(ICamera &camera, const LookAtParameters &lookAtParameters) {
	auto c = static_cast<Camera&>(camera);
	c.m_position = lookAtParameters.position;
	c.m_target = lookAtParameters.target;
	c.m_up = lookAtParameters.up;
	c.m_view = glm::lookAt(lookAtParameters.position, lookAtParameters.target, lookAtParameters.up);
}

} // namespace meow