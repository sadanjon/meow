#ifndef VECTOR3_H 
#define VECTOR3_H

namespace meow {
	
class Vector3 {
	float *m_vec;
public:
	Vector3() :
		m_vec(new float[3]) {
		m_vec[0] = 0;
		m_vec[1] = 0;
		m_vec[2] = 0;
	}

	Vector3(float x, float y, float z) :
		m_vec(new float[3])  {
		m_vec[0] = x;
		m_vec[1] = y;
		m_vec[2] = z;
	}

	Vector3(float *vec) :
		m_vec(new float[3])  {
		m_vec[0] = vec[0];
		m_vec[1] = vec[1];
		m_vec[2] = vec[2];
	}

	Vector3(const Vector3 &vec) :
		m_vec(new float[3])  {
		m_vec[0] = vec[0];
		m_vec[1] = vec[1];
		m_vec[2] = vec[2];
	}

	Vector3(Vector3 &&vec) :
		Vector3() {
		swap(*this, vec);
	}

	virtual ~Vector3() {
		delete[] m_vec;
	}

	Vector3 &operator=(Vector3 vec) {
		swap(*this, vec);
		return *this;
	}

	float &operator[](int i) const {
		return m_vec[i];
	}

	float *getArray() const {
		return m_vec;
	}

	bool operator==(const Vector3 &v) const {
		return m_vec[0] == v.m_vec[0] &&
			m_vec[1] == v.m_vec[1] &&
			m_vec[2] == v.m_vec[2];
	}

	bool operator!=(const Vector3 &v) const {
		return !(*this == v);
	}
	
private:
	void swap(Vector3 &a, Vector3 &b) {
		std::swap(a.m_vec, b.m_vec);
	}
	
};

} // namespace meow

#endif // VECTOR3_H