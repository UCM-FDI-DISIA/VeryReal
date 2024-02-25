#pragma once

#include <unordered_map>
#include "Entity_Names.h"
#include "Entity.h"
using namespace std;
class Scene
{

protected:
	//Mapa de: Clave: nombre de Entidad, Valor: puntero a esa entidad
	unordered_map<entity_name, Entity*> entities_map;
	list<entity_name> entities_list_removed;
	bool is_active;
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
	void  Update(const double& dt);
	inline void SetActive(bool active) { is_active = active; }
	inline bool GetActive() { return is_active; }
	
};
