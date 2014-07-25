#ifndef CAMERA_H 
#define CAMERA_H

#include "icamera.h"

namespace meow {
	
class Camera : public ICamera {
	friend class CameraService;

	glm::mat4 m_view;
	glm::mat4 m_projection;
	glm::vec3 m_position;
	glm::vec3 m_target;
	glm::vec3 m_up;
public:
	const glm::mat4 &getViewMatrix() const override;
	const glm::mat4 &getProjectionMatrix() const override;
	const glm::vec3 &getPosition() const override;
	const glm::vec3 &getTarget() const override;
	const glm::vec3 &getUp() const override;
};

inline const glm::mat4 &Camera::getViewMatrix() const {
	return m_view;
}

inline const glm::mat4 &Camera::getProjectionMatrix() const {
	return m_projection;
}

inline const glm::vec3 &Camera::getPosition() const {
	return m_position;
}

inline const glm::vec3 &Camera::getTarget() const {
	return m_target;
}

inline const glm::vec3 &Camera::getUp() const {
	return m_up;
}

} // namespace meow

#endif // CAMERA_H