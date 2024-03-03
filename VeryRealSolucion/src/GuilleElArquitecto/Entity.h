#pragma once
#ifndef ENTITY
#define ENTITY
#include <unordered_map>
#include "Component.h"

using namespace std;
using entity_name = string;
namespace VeryReal {


	class Entity
	{
	private:
		//Mapa de Componentes: clave: nombre, valor:puntero a ese Componente
		unordered_map<component_name, VeryReal::Component*> components_map;

		//lista de componentes a remover, porque no están activos
		list<component_name> components_list_removed;

		bool is_alive;
		entity_name name;

	public:
		Entity();
		virtual ~Entity();

		//Añade componente a la Entidad
		template<typename T, typename ...Ts>
		inline T* AddComponent(component_name c_name, Ts && ... args) {
			T* component = new T(forward<Ts>(args)...);
			//si quieres añadir de nuevo un componente ya existente, lo sobrescribe
			RemoveComponent(c_name);
			components_map.insert({ c_name,component });
			//quizas initcomponent
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
		void Update();
		void Refresh();

		//Indica el nombre de la Entidad
		inline void SetName(entity_name name) { this->name = name; }
		inline entity_name GetName() { return name; }
	};
}
#endif

