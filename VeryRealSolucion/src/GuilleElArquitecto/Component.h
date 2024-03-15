#pragma once
#ifndef COMPONENT
#define COMPONENT

namespace VeryReal {
	class Entity;
	class VariantClass;	

	class Component	//CLASE ABSTRACTA
	{
	private:
		bool active = true;
		VeryReal::Entity* entity = nullptr;
		
	public:
		Component() {}
		virtual ~Component() {}
		virtual void Update(const double& dt) {}

		//Indica si el Componente está activo o no
		inline void SetActive(bool active) { this->active = active; }
		inline bool GetActive() { return active; }

		//El componente necesita saber cual es su entidad, para acceder a otros componentes de esta
		inline void SetEntity(VeryReal::Entity* entity) { this->entity = entity; }
		inline VeryReal::Entity* GetEntity() { return entity; }

		virtual void OnCollisionEnter(Entity* other) {};
		virtual void OnCollisionStay(Entity* other) {};
		virtual void OnCollisionExit(Entity* other) {};

		
		//Damos nombre a nuestro componente
		/*inline void SetName(component_name name) { this->name = name; }
		inline component_name GetName() { return name; }*/
	};
}
#endif
