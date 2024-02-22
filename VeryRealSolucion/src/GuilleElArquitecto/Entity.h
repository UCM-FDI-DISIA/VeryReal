#pragma once
#include <unordered_map>
#include "Component_Names.h"
#include "Component.h"
using namespace std;
class Entity
{
	//COSAS BASICAS:
	//-Constructora
	//-Destructora
	// 
	//AddComponent
	//RemoveComponent
	//hasComponent
	//getComponent
	// 
	//setActive
	//getActive

	//start
	//update
private:
	unordered_map<component_name, Component*> components;
	bool is_alive;
public:
	//mirar si queremos que reciba algo, de momento PedroPablo gestiona la escena
	Entity();
	virtual ~Entity();

	void AddComponent(component_name component);
	void RemoveComponent(component_name component);
	inline bool HasComponent(component_name component) {
		
	}
	inline Component* GetComponent(component_name component) {
		return components[component];
	}
	inline void SetActive(bool active) {
		is_alive = active;
	}
	inline bool GetActive() {
		return is_alive;
	}

	void Update();
};

