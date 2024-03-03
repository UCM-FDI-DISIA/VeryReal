#pragma once
#ifndef MANAGER
#define MANAGER
#include "Singleton.h"

//CLASE ABSTRACTA, hereda de Singleton 
namespace VeryReal {
	template<typename T>
	class Manager : public VeryReal::Singleton<T> {
		friend VeryReal::Singleton<T>;
	private:

	public:
		Manager() {}
		virtual ~Manager() {}
		virtual void Update(const double& dt) {}
	};
}
#endif
