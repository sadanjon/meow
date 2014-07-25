#ifndef ICAMERA_H 
#define ICAMERA_H

#include "glm/matrix.hpp"
#include "glm/vec3.hpp"

namespace meow {
	
class ICamera {
public:
	virtual ~ICamera() {}
	
	virtual const glm::mat4 &getViewMatrix() const = 0;
	virtual const glm::mat4 &getProjectionMatrix() const = 0;
	virtual const glm::vec3 &getPosition() const = 0;
	virtual const glm::vec3 &getTarget() const = 0;
	virtual const glm::vec3 &getUp() const = 0;
};

} // namespace meow

#endif // ICAMERA_H