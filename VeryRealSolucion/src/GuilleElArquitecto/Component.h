#pragma once
#ifndef COMPONENT
#define COMPONENT
using namespace std;

namespace VeryReal {
	class Entity;
	//using component_name = string;

	class Component	//CLASE ABSTRACTA
	{
	private:
		bool active = true;
		VeryReal::Entity* entity = nullptr;
		
	public:
		Component() {}
		virtual ~Component() {}
		virtual void Update() {}

		//Indica si el Componente está activo o no
		inline void SetActive(bool active) { this->active = active; }
		inline bool GetActive() { return active; }

		//El componente necesita saber cual es su entidad, para acceder a otros componentes de esta
		inline void SetEntity(VeryReal::Entity* entity) { this->entity = entity; }
		inline VeryReal::Entity* GetEntity() { return entity; }

		//Damos nombre a nuestro componente
		/*inline void SetName(component_name name) { this->name = name; }
		inline component_name GetName() { return name; }*/
	};
}
#endif
