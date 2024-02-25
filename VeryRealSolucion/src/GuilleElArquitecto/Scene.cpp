#include "Scene.h"
Scene::Scene() {

}
Scene::~Scene() {

}
Entity* Scene::AddEntity(entity_name e_name) {

}
void Scene::RemoveEntity(entity_name e_name) {
	if (entities_map.find(e_name) != entities_map.end()) {
		delete entities_map.at(e_name);
		entities_map.erase(e_name);
	}
}
Entity* Scene::GetEntity(entity_name e_name) {
	if (!HasEntity(e_name)) {
		cerr << "No existe dicha entidad\n";
		return nullptr;
	}
	return entities_map.at(e_name);
}
void  Scene::Update(const double& dt) {
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
void Scene::Refresh() {
	for (auto e = entities_list_removed.begin(); e != entities_list_removed.end();) {
		RemoveEntity(*e);
		auto p = e;
		p++;
		entities_list_removed.pop_front();
		e = p;
	}
}