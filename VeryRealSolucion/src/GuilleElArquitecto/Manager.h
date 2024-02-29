#pragma once
#include "Singleton.h"
class Manager:public Singleton<Manager> {
	friend Singleton<Manager>;

private:

public:
	Manager(){}
	virtual ~Manager(){}
	virtual void Update(const double& dt) {}
};

