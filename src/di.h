#ifndef DI_H 
#define DI_H

#include <unordered_map>
#include <typeinfo>
#include <string>

namespace di {

struct ITypeInfo {
	virtual const std::type_info *getTypeInfo() = 0;
	virtual void *createNew() = 0;

	struct TypeInfoHasher {
		size_t operator()(ITypeInfo *ti) {
			return ti->getTypeInfo()->hash_code();
		}
	};

	struct TypeInfoComparer {
		bool operator()(ITypeInfo *a, ITypeInfo *b) {
			return a->getTypeInfo()->hash_code() == b->getTypeInfo()->hash_code();
		}
	};
};

template<typename T>
struct TypeInfo : public ITypeInfo {
	const std::type_info *getTypeInfo() {
		return &typeid(T);
	}

	void *createNew() {
		return new T();
	}
};

template<typename T>
struct InterfaceTypeInfo : public ITypeInfo {
	const std::type_info *getTypeInfo() {
		return &typeid(T);
	}

	void *createNew() {
		return NULL;
	}

};


class Registry {
	typedef std::unordered_map<ITypeInfo*, ITypeInfo*, ITypeInfo::TypeInfoHasher, ITypeInfo::TypeInfoComparer> TypeMap;
	TypeMap m_registry;
public:
	Registry();

	static Registry *getInstance() {
		static Registry *instance = new Registry();
		return instance;
	}

	template<typename I, typename T>
	void registerType() {
		m_registry.insert(std::pair<ITypeInfo*, ITypeInfo*>(new InterfaceTypeInfo<I>(), new TypeInfo<T>()));
	}

	template<typename I>
	I *createNew() {
		auto t = m_registry.find(&InterfaceTypeInfo<I>());
		if (t == m_registry.end())
			throw new std::exception();
		return reinterpret_cast<I*>(t->second->createNew());
	}

private:
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
		return Registry::getInstance()->createNew<T>();
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
