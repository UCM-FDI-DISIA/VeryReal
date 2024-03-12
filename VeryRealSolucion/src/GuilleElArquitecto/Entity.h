#pragma once
#ifndef ENTITY
#define ENTITY
#include "Creator.h"

namespace VeryReal {
	using component_name = std::string;
	class Component;
	class Entity
	{
	private:
		//Mapa de Componentes: clave: nombre, valor:puntero a ese Componente
		std::unordered_map<component_name, Component*> components_map;

		//lista de componentes a remover, porque no están activos
		std::list<component_name> components_list_removed;

		bool is_alive;
	public:
		Entity();
		virtual ~Entity();

		//Añade componente a la Entidad
		
		inline Component* AddComponent(component_name c_name) {
			Component* component= Creator::Instance()->CallSpecificCreator(c_name);
			/*	T* component = new T(forward<Ts>(args)...);*/
			//si quieres añadir de nuevo un componente ya existente, lo sobrescribe
			RemoveComponent(c_name);
			components_map.insert({ c_name,component});
			//quizas initcomponentpai
			return component;
		}
		//Remueve el Componente de la Entidad en la que se encuentra
		void RemoveComponent(component_name c_name);

		//Indica si la entidad tiene este componente
		inline bool HasComponent(component_name c_name) {
			return components_map.count(c_name);
		}

		//Devuelve el componente especifico y si no esta devuelve nullptr
		template<typename T>
		inline T* GetComponent(component_name c_name) {
			if (!HasComponent(c_name)) {
				return nullptr;
			}
			return static_cast<T*>(components_map.at(c_name));
		}

		//Indican si la entidad está activa o no
		inline void SetActive(bool active) { is_alive = active; }
		inline bool GetActive() { return is_alive; }

		/*
			Recorremos de primeras con un for el mapa:
				-->Comprobamos si el componente está activo-->hacemos su Update
				-->Si no está activo, lo añadimos a una lista de componentes no activos
				(Hecho de esta forma para evitar llamadas a null, a componentes ya removidos, en el propio Update)

			Posteriormente, recorremos la lista de componentes a eliminar
				-->Removemos el componente del mapa
				-->Removemos el componente de la lista

			Elimina de manera segura los componentes
		*/
		void Update(const double& dt);
		void Refresh();

		//Indica el nombre de la Entidad
		//inline void SetName(entity_name name) { this->name = name; }
		//inline entity_name GetName() { return name; }

		void OnCollisionEnter(Entity* other);
		void OnCollisionExit(Entity* other);
		void OnCollisionStay(Entity* other);




	};
}
#endif

