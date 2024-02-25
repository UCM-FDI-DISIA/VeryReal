#include "Entity.h"
Entity::Entity() {

}
Entity::~Entity() {

}

void Entity::RemoveComponent(component_name c_name) {
	//para que no te de error si el componente no est� incluido y tu quieres removerlo
	if (HasComponent(c_name)) {
		delete components_map.at(c_name);
		components_map.erase(c_name);
	}
}
/*
Recorremos de primeras con un for el mapa:
	-->Comprobamos si el componente est� activo-->hacemos su Update
	-->Si no est� activo, lo a�adimos a una lista de componentes no activos
	(Hecho de esta forma para evitar llamadas a null, a componentes ya removidos, en el propio Update)

Posteriormente, recorremos la lista de componentes a eliminar
	-->Removemos el componente del mapa
	-->Removemos el componente de la lista

*/
void Entity::Update() {
	for (auto c : components_map) {
		if (c.second->GetActive()) {
			c.second->Update();
		}
		else {
			components_list_removed.push_back(c.first);
		}
	}
	Refresh();
}
void Entity::Refresh() {
	for (auto c = components_list_removed.begin(); c != components_list_removed.end();) {
		RemoveComponent(*c);
		auto p = c;
		p++;
		components_list_removed.pop_front();
		c = p;
	}
}