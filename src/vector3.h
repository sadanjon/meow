#ifndef VECTOR3_H 
#define VECTOR3_H

namespace meow {
	
class Vector3 {
public:
	float x, y, z;
	
	Vector3() : x(0), y(0), z(0) {}
	Vector3(float x, float y, float z) : x(x), y(y), z(z) {}
	Vector3(const Vector3 &other) : x(other.x), y(other.y), z(other.z) {}
	Vector3 &operator=(const Vector3 &rhs) {
		x = rhs.x;
		y = rhs.y;
		z = rhs.z;
	}

	inline void set(float x, float y, float z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}
};

} // namespace meow

#endif // VECTOR3_H