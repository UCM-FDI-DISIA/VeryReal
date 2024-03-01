#include "SceneManager.h"
SceneManager::SceneManager() {}
SceneManager::~SceneManager() {}

void SceneManager::Update(const double& dt) {
	for (auto it : scenes_list) if (it->GetActive())it->Update();
	Refresh();
	
}

void SceneManager::Refresh() {
	for (auto it : scenes_list)if (it->GetToEliminate())RemoveScene(it->GetName());
}
Scene* SceneManager::AddScene(scene_name name) {
	RemoveScene(name);
	Scene* scene = new Scene();
	scenes_list.push_back(scene);
	ActivationScene(name, true);
	EliminationScene(name, false);
}
void SceneManager::RemoveScene(scene_name name) {
	for (auto it : scenes_list) if (it->GetName() == name) scenes_list.remove(it);
}
void SceneManager::ActivationScene(scene_name name, bool active) {
	for (auto it : scenes_list) if (it->GetName() == name)it->SetActive(active);
}
/*void DesactivateScene(scene_name name) {
	for (auto it : scenes_list) if (it->GetName() == name)it->SetActive(false);
}*/
void SceneManager::EliminationScene(scene_name name, bool to_eliminate) {
	for (auto it : scenes_list) if (it->GetName() == name)it->SetToEliminate(to_eliminate);
}
