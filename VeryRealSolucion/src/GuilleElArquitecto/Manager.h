#pragma once
#include "Singleton.h"

//CLASE ABSTRACTA, hereda de Singleton 
template<typename T>
class Manager : public Singleton<T>{
	friend Singleton<T>;
private:

public:
	Manager(){}
	virtual ~Manager(){}
	virtual void Update(const double& dt) {}
};

