#pragma once
#ifndef SINGLETON
#define SINGLETON
#include <memory>

namespace VeryReal {
	template<class T>
class Singleton
	{
	private:
		//unica instancia de la clase de tipo T
		static std::unique_ptr<T> instance_pointer;

	protected:
		Singleton() {};
	public:
		VeryReal::Singleton<T>& operator=(const VeryReal::Singleton<T>& o) = delete;
		Singleton(const VeryReal::Singleton<T>& o) = delete;
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
			}
			return instance_pointer.get();
		}

		//elimina el puntero de la instancia
        static void Delete() {
            instance_pointer.reset(); 
        }
	};

	template<typename T>
	std::unique_ptr<T> VeryReal::Singleton<T>::instance_pointer;
}
#endif