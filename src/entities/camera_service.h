#ifndef CAMERA_SERVICE_H 
#define CAMERA_SERVICE_H

#include "icamera_service.h"

namespace meow {
	
class CameraService : public ICameraService {
public:
	std::shared_ptr<ICamera> create() override;
	void perspective(ICamera &camera, const PerspectiveParameters &perspectiveParameters) override;
	void lookAt(ICamera &camera, const LookAtParameters &lookAtParameters) override;
};

} // namespace meow

#endif // CAMERA_SERVICE_H