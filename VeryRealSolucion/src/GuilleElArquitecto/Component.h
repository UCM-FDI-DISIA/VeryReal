#pragma once
#ifndef COMPONENT
#define COMPONENT

#include "export.h"
namespace VeryReal {
	class Entity;
	class VariantClass;	

	class VERYREAL_GUILLEELARQUITECTO Component	//CLASE ABSTRACTA
	{
	private:
		bool active = true;
		VeryReal::Entity* entity = nullptr;

	protected: 
		int orden = 0;
		
	public:
		Component() {}
		virtual ~Component();
		virtual void Update(const double& dt) {}

		// Indica si el Componente está activo o no
		inline void SetActive(bool active) { this->active = active; }

		// Devuelve un valor que indica si el componente esta o no activo
		inline bool GetActive() { return active; }

		//El componente necesita saber cual es su entidad, para acceder a otros componentes de esta
		inline void SetEntity(VeryReal::Entity* entity) { this->entity = entity; }

		//Devuelve la entidad que contiene el componente
		inline VeryReal::Entity* GetEntity() { return entity; }


		inline int GetOrden() { return orden; }
		inline void SetOrden(int ord) { orden = ord; }

		virtual void OnCollisionEnter(Entity* other) {};
		virtual void OnCollisionStay(Entity* other) {};
	};
}
#endif
