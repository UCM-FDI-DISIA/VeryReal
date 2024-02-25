#pragma once
#include <unordered_map>
#include "Component_Names.h"
#include "Component.h"
#include <iostream>
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
	list<component_name> components_list_removed;
	bool is_alive;
public:
	//mirar si queremos que reciba algo, de momento PedroPablo gestiona la escena
	Entity();
	virtual ~Entity();
	template<typename T, typename ...Ts>
	inline T* AddComponent(component_name c_name, Ts && ... args) {
		T* component = new T(forward<Ts>(args)...);
		//si quieres añadir de nuevo un componente ya existente, lo sobrescribe
		RemoveComponent(c_name);
		components_map.insert({c_name,component});
		//quizas initcomponent
		return component;
	}
	void RemoveComponent(component_name c_name);

	inline bool HasComponent(component_name c_name) {
		return components_map.count(c_name);
	}
	template<typename T>
	inline T* GetComponent(component_name c_name) {
		if (!HasComponent(c_name)) {
			cerr << "No existe dicho componente\n";
			return nullptr;
		}
		return static_cast<T*>(components_map.at(c_name));
	}

	inline void SetActive(bool active) { is_alive = active; }
	inline bool GetActive() { return is_alive; }

	void Update();
	void Refresh();
};

