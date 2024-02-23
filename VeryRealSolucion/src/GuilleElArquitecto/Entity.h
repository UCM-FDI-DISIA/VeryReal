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
	unordered_map<component_name, Component*> components_map;
	bool is_alive;
public:
	//mirar si queremos que reciba algo, de momento PedroPablo gestiona la escena
	Entity();
	virtual ~Entity();
	template<typename T, typename ...Ts>
	inline T* AddComponent(component_name c_name, Ts && ... args) {
		T* component = new T(forward<Ts>(args)...);
		RemoveComponent(c_name);
		components_map.insert({c_name,component});
		//quizas initcomponent
		return component;
	}
	void RemoveComponent(component_name c_name);
	inline bool HasComponent(component_name c_name) {
		return components_map.count(c_name);
	}
	inline Component* GetComponent(component_name c_name) {
		return components_map.at(c_name);
	}
	inline void SetActive(bool active) {
		is_alive = active;
	}
	inline bool GetActive() {
		return is_alive;
	}

	void Update();
};

