#ifndef DI_H 
#define DI_H

#define DI_USE(I, T) \
	namespace di { \
	template<> \
	struct Injection<I> { \
		typedef T ImplementationType; \
	}; \
	}

namespace di {

class DummyType {};

template<class T>
struct Injection {
	typedef DummyType ImplementationType;
};

template<typename T>
class Component {
	static T *instance;
	static int count;
public:
	Component() {
		ref();
	}
	
	~Component() { 
		deref(); 
	}

	T &operator*() {
		return *instance;
	}

	T *operator->();

private:
	void ref() {
		count += 1;
		if (instance == 0) {
			instance = createNew();
		}
	}

	void deref() {
		count -= 1;
		if (count == 0) {
			delete instance;
			instance = 0;
		}
	}

	T *createNew() {
		return new typename Injection<T>::ImplementationType();
	}
};

template<typename T>
T *Component<T>::instance = 0;

template<typename T>
int Component<T>::count = 0;

template<typename T>
T *Component<T>::operator->() {
	return instance;
}

} // namespace di

#endif // DI_H
