#pragma once
#include <memory>
template<class T>
class Singleton
{
private:


protected:
	Singleton() {};
	//The only instance of class T
	static std::unique_ptr<T> instance_pointer;

public:
	Singleton<T>& operator=(const Singleton<T>& o) = delete;
	Singleton(const Singleton<T>& o) = delete;
	virtual ~Singleton() {}

	//devuelve la clase singelton:
		//->Si no existe lo crea llamando a Init
		//->Si existe lo devuelve
	static T* Instance() {
		if (instance_pointer.get() == nullptr)
			return Init();
		return instance_pointer.get();
	}

	template<typename ...Targs>
	static T* Init(Targs &&...args) {
		if (instance_pointer.get() == nullptr) {
			instance_pointer.reset(new T(std::forward<Targs>(args)...));
			//PREGUNTAR CERROR
			//std::cout << "Singleton: Instance of " << typeid(T).name() << " created.\n";
		}
		else {
			//PREGUNTAR CERROR
			//std::cout << "Singleton error: There already is an instance of class " << typeid(T).name() << ".\n";
		}
		return instance_pointer.get();
	}

	static void Delete() {
		if (instance_pointer.get() != nullptr)
			delete instance_pointer.release();
	}
};

template<typename T>
std::unique_ptr<T> Singleton<T>::instance_pointer;