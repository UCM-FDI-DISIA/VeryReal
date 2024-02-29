#pragma once

#include <unordered_map>
#include "Entity.h"
using namespace std;

using scene_name = string;
class Scene
{

protected:
	//Mapa de: Clave: nombre de Entidad, Valor: puntero a esa entidad
	unordered_map<entity_name, Entity*> entities_map;
	list<entity_name> entities_list_removed;
	bool is_active;
	bool to_eliminate = false;
	scene_name name;

public:
	//Ppsibles métodos para hacer en un futuro: 
	// ProcessNewEntities: te añade entidades a un vector y una vez finalizado el update es cuando las añade al mapa
	//inline unordered_map<entity_name, Entity*> GetMapEntity() devuelve el mapa de entidades
	Scene();
	virtual ~Scene();
	Entity* AddEntity(entity_name e_name);
	void RemoveEntity(entity_name e_name);
	inline bool HasEntity(entity_name e_name) {
		return entities_map.count(e_name);
	}
	Entity* GetEntity(entity_name e_name);
	//elimina de manera segura las entidades del mapa
	void Refresh();
	void  Update();

	inline void SetActive(bool active) { is_active = active; }
	inline bool GetActive() { return is_active; }

	inline void SetToEliminate(bool to_eliminate) { this->to_eliminate = to_eliminate; }
	inline bool GetToEliminate() { return to_eliminate; }

	inline void SetName(scene_name name) { this->name = name; }
	inline scene_name GetName() { return name; }
	
};
