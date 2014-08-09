#ifndef OPTIONAL_H 
#define OPTIONAL_H

namespace meow {
	
template<typename T>
class Optional {
	T m_value;
	bool m_exists;
public:
	Optional() :
		m_exists(false) {
	}

	Optional(T value) :
		m_value(value),
		m_exists(true) {
	}

	Optional(const Optional<T> &optional) :
		m_value(optional.m_value),
		m_exists(optional.m_exists) {
	}

	Optional(Optional<T> &&optional) {
		swap(optional);
	}

	Optional &operator=(Optional<T> optional) {
		swap(optional);
		return *this;
	}

	Optional &operator=(T value) {
		m_value = value;
		m_exists = true;
		return *this;
	}

	const T &get() const {
		return m_value;
	}

	void set(const T &value) const {
		m_value = value;
	}

	bool exists() const {
		return m_exists;
	}

	void reset() {
		m_exists = false;
	}

	bool operator==(const Optional<T> &other) const {
		return m_exists == other.m_exists && m_value == other.m_value;
	}

	bool operator!=(const Optional<T> &other) const {
		return !(*this == other);
	}

private:
	void swap(Optional &optional) {
		std::swap(m_value, optional.m_value);
		std::swap(m_exists, optional.m_exists);
	}
};

template<typename T>
Optional<T> createOptional() {
	return Optional<T>();
}

template<typename T>
Optional<T> createOptional(T value) {
	return Optional<T>(value);
}


} // namespace meow

#endif // OPTIONAL_H