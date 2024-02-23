#pragma once
class Entity;
class Component	//CLASE ABSTRACTA
{
	
private:
	bool active = true;
	Entity* entity;

public:
	Component() {}
	virtual ~Component() {}
	//quizas INIT
	virtual void Update() {}
	
	inline void SetActive(bool active) {this->active = active;}
	inline bool GetActive() { return active; }
	
	//El componente necesita saber cual es su entidad, para acceder a otros componentes de esta
	inline void SetEntity(Entity* entity) { this->entity = entity; }
	inline Entity* GetEntity() { return entity; }
};

