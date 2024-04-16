#pragma once
#ifndef MANAGER
#define MANAGER
#include "Singleton.h"
#include "export.h"
//CLASE ABSTRACTA, hereda de Singleton 
namespace VeryReal {
	template<typename T>
    class  Manager : public Singleton<T> {
		friend Singleton<T>;
	protected:
        Manager(){};
	public:
    
		virtual ~Manager() {}
		virtual void Update(const double& dt) {}
	};
}
#endif
