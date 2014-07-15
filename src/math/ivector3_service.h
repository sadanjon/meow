#ifndef IVECTOR3_SERVICE_H 
#define IVECTOR3_SERVICE_H

namespace meow {
	
class IVector3Service {
public:
	virtual ~IVector3Service() {}

	virtual float *create(float x, float y, float z) = 0;
	virtual float *createZero() = 0;
	virtual void zero(float *vector3) = 0;
	virtual void set(float *vector3, float x, float y, float z) = 0;
};

} // namespace meow

#endif // IVECTOR3_SERVICE_H