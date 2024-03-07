#include "SceneManager.h"
#include "Scene.h"
//VeryReal::SceneManager::SceneManager() {}
//VeryReal::SceneManager::~SceneManager() {}

void VeryReal::SceneManager::Update(const double& dt) {
	for (auto it : scenes_list) if (it->GetActive())it->Update();
	Refresh();
	
}

void VeryReal::SceneManager::Refresh() {
	for (auto it : scenes_list)if (it->GetToEliminate())RemoveScene(it->GetName());
}
VeryReal::Scene* VeryReal::SceneManager::AddScene(scene_name name) {
	RemoveScene(name);
	Scene* scene = new Scene();
	scene->SetName(name);
	scenes_list.push_back(scene);
	ActivationScene(name, true);
	EliminationScene(name, false);

	return scene;
}
void VeryReal::SceneManager::RemoveScene(scene_name name) {
	for (auto it : scenes_list) if (it->GetName() == name) scenes_list.remove(it);
}
void VeryReal::SceneManager::ActivationScene(scene_name name, bool active) {
	for (auto it : scenes_list) if (it->GetName() == name)it->SetActive(active);
}
/*void DesactivateScene(scene_name name) {
	for (auto it : scenes_list) if (it->GetName() == name)it->SetActive(false);
}*/
void VeryReal::SceneManager::EliminationScene(scene_name name, bool to_eliminate) {
	for (auto it : scenes_list) if (it->GetName() == name)it->SetToEliminate(to_eliminate);
}
VeryReal::Scene* VeryReal::SceneManager::GetScene(scene_name name) { 
	for (auto c : scenes_list) if (c->GetName() == name)return c; 
}
