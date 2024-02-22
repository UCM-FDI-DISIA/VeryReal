#pragma once

#include <unordered_map>
#include "Entity_Names.h"
#include "Entity.h"
using namespace std;
class Scene
{

private:
	//Mapa de: Clave: nombre de Entidad, Valor: puntero a esa entidad
	unordered_map<entity_name, Entity*> entities;
public:
	Scene() {
		/*Entity* ent;
		entities.insert({ PLAYER,ent });*/
	}
	
};

