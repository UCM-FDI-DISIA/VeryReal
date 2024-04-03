#pragma once
#ifndef MANAGER
#define MANAGER
#include "Singleton.h"
#include "export.h"
//CLASE ABSTRACTA, hereda de Singleton 
namespace VeryReal {
	template<typename T>
    class VERYREAL_API Manager : public Singleton<T> {
		friend Singleton<T>;
	private:

	public:
		Manager() {}
		virtual ~Manager() {}
		virtual void Update(const double& dt) {}
	};
}
#endif
