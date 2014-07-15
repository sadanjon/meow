#ifndef VECTOR3_SERVICE_H 
#define VECTOR3_SERVICE_H

#include "ivector3_service.h"

namespace meow {
	
class Vector3Service : public IVector3Service {
public:
	float *createZero();
	float *create(float x, float y, float z);

	void zero(float *vector3);
	void set(float *vector3, float x, float y, float z);
};

} // namespace meow

#endif // VECTOR3_SERVICE_H