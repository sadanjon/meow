#ifndef VECTOR2_H 
#define VECTOR2_H

namespace meow {
	
class Vector2 {
	float *m_vec;
public:
	Vector2() :
		m_vec(new float[2]) {
		m_vec[0] = 0;
		m_vec[1] = 0;
	}

	Vector2(float x, float y) :
		m_vec(new float[2])  {
		m_vec[0] = x;
		m_vec[1] = y;
	}

	Vector2(float *vec) :
		m_vec(new float[2])  {
		m_vec[0] = vec[0];
		m_vec[1] = vec[1];
	}

	Vector2(const Vector2 &vec) :
		m_vec(new float[2])  {
		m_vec[0] = vec[0];
		m_vec[1] = vec[1];
	}

	Vector2(Vector2 &&vec) :
		Vector2() {
		swap(*this, vec);
	}

	virtual ~Vector2() {
		delete[] m_vec;
	}

	Vector2 &operator=(Vector2 vec) {
		swap(*this, vec);
		return *this;
	}

	float &operator[](int i) const {
		return m_vec[i];
	}

	float *getArray() const {
		return m_vec;
	}

	bool operator==(const Vector2 &v) const {
		return m_vec[0] == v.m_vec[0] &&
			m_vec[1] == v.m_vec[1];
	}

	bool operator!=(const Vector2 &v) const {
		return !(*this == v);
	}

private:
	void swap(Vector2 &a, Vector2 &b) {
		std::swap(a.m_vec, b.m_vec);
	}
	
};

} // namespace meow

#endif // VECTOR2_H