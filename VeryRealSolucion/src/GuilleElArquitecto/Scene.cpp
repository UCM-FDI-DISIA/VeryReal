#include "Scene.h"
VeryReal::Scene::Scene() {}
VeryReal::Scene::~Scene() {}

VeryReal::Entity* VeryReal::Scene::AddEntity(entity_name e_name) {
	Entity* entity = new Entity();
	RemoveEntity(e_name);
	entities_map.insert({ e_name,entity });
	return entity;
}

void VeryReal::Scene::RemoveEntity(entity_name e_name) {
	if (HasEntity(e_name)) {
		delete entities_map.at(e_name);	//eliminas el puntero
		entities_map.erase(e_name);	//eliminas del mapa
	}
}

void  VeryReal::Scene::Update() {
	for (auto e : entities_map) {
		if (e.second->GetActive()) {
			e.second->Update();
		}
		else {
			entities_list_removed.push_back(e.first);
		}
	}
	Refresh();
}

void VeryReal::Scene::Refresh() {
	for (auto e = entities_list_removed.begin(); e != entities_list_removed.end();) {
		RemoveEntity(*e);
		auto p = e;
		p++;
		entities_list_removed.pop_front();
		e = p;
	}
}
