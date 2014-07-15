#include "vector3_service.h"

namespace meow {

float *Vector3Service::createZero() {
	auto v = new float[3];
	v[0] = 0;
	v[1] = 0;
	v[2] = 0;
	return v;
}

float *Vector3Service::create(float x, float y, float z) {
	auto v = new float[3];
	v[0] = x;
	v[1] = y;
	v[2] = z;
	return v;	
}

void Vector3Service::zero(float *vector3) {
	vector3[0] = 0;
	vector3[1] = 0;
	vector3[2] = 0;
}

void Vector3Service::set(float *vector3, float x, float y, float z) {
	vector3[0] = x;
	vector3[1] = y;
	vector3[2] = z;
}

} // namespace meow
