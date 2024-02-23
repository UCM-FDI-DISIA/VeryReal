#pragma once
class Entity;
class Component
{
	
private:
	bool active;
	Entity* entity;
	int a = 0;

public:
	Component(int a) {
		this->a = a;
	}
	virtual ~Component() {

	}
	void Update() {

	}

	/*inline void SetActive(bool active) {this->active = active;}
	inline bool GetActive() { return active; }*/
	//COSAS BASICAS:
	//-Constructora
	//-Destructora
	// 
	// 
	//setActive
	//getActive

	/*void SetEntity(Entity* entity);
	inline Entity* GetEntity() { return entity; }*/
	//setEntidad
	//getEntidad
	// 
	//update
};

