#pragma once
#ifndef SCENE
#define SCENE
#include <unordered_map>
#include <string>
#include "export.h"

using scene_name = std::string;
using entity_name = std::string;

#pragma warning(disable : 4251)

namespace VeryReal {
	class Entity;
	class VERYREAL_API Scene {
	private:
		//Mapa de: Clave: nombre de Entidad, Valor: puntero a esa entidad
		std::unordered_map<entity_name, Entity*> entities_map;

		//Lista de entidades a remover
		std::list<entity_name> entities_list_removed;

		bool is_active = true;
		bool to_eliminate = false;
		scene_name name;

	public:

		Scene();
		virtual ~Scene();

		//añade la entidad a la escena
		Entity* AddEntity(entity_name e_name);


		//eliminas la entidad de la escena
		void RemoveEntity(entity_name e_name);

		//devuelve si la escena tiene esa entidad
		inline bool HasEntity(entity_name e_name) {
			return entities_map.count(e_name);
		}

		//devuelve la entidad si la escena la tiene y si no nullptr;
		inline Entity* GetEntity(entity_name e_name) {
			if (!HasEntity(e_name)) return nullptr;
			return entities_map.at(e_name);
		}

		inline std::unordered_map<entity_name, Entity*> GetEntities() { 
			return entities_map;
		}
		
		// Añade el prefab a la escena
		Entity* CreatePrefab(std::string prefab_name, entity_name e_name);

		/*
	Recorremos de primeras con un for el mapa:
		-->Comprobamos si la entidad está activa-->hacemos su Update
		-->Si no está activa, lo añadimos a una lista de entidades no activas
		(Hecho de esta forma para evitar llamadas a null, a entidades ya removidos, en el propio Update)

	Posteriormente, recorremos la lista de entidades a eliminar
		-->Removemos la entidad del mapa
		-->Removemos la entidad de la lista
	//elimina de manera segura las entidades del mapa

	*/
		void  Update(const double& dt);
		void Refresh();

		//Indica si la  Escena esta activa
		inline void SetActive(bool active) { is_active = active; }
		inline bool GetActive() { return is_active; }

		//Indica si la escena se tiene que eliminar
		inline void SetToEliminate(bool to_eliminate) { this->to_eliminate = to_eliminate; }
		inline bool GetToEliminate() { return to_eliminate; }

		//Indica el nombre de la escena
		inline void SetName(scene_name name) { this->name = name; }
		inline scene_name GetName() { return name; }

	};
}

#pragma warning(default : 4251)

#endif