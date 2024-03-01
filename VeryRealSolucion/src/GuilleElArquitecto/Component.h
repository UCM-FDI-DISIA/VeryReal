#pragma once
#include <string>

class Entity;
using namespace std;
using component_name = string;

class Component	//CLASE ABSTRACTA
{
private:
	bool active = true;
	Entity* entity;
	component_name name;
public:
	Component() {}
	virtual ~Component() {}
	virtual void Update() {}
	
	//Indica si el Componente está activo o no
	inline void SetActive(bool active) {this->active = active;}
	inline bool GetActive() { return active;}
	
	//El componente necesita saber cual es su entidad, para acceder a otros componentes de esta
	inline void SetEntity(Entity* entity) { this->entity = entity; }
	inline Entity* GetEntity() { return entity; }

	//Damos nombre a nuestro componente
	inline void SetName(component_name name) { this->name = name; }
	inline component_name GetName() { return name; }
};

