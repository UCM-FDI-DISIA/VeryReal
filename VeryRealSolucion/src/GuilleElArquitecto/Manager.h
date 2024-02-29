#pragma once
#include "Singleton.h"

//CLASE ABSTRACTA, hereda de Singleton 
class Manager:public Singleton<Manager> {
	friend Singleton<Manager>;

private:

public:
	Manager(){}
	virtual ~Manager(){}
	virtual void Update(const double& dt) {}
};

