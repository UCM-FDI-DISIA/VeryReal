#include "SceneManager.h"
#include "Scene.h"
using namespace std;

VeryReal::SceneManager::~SceneManager() {

    for (auto it : scenes_list) {
        delete (it);
    }
};


void VeryReal::SceneManager::Update(const double& dt) {
    for (auto it : scenes_list)
        if (it->GetActive()) it->Update(dt);
    Refresh();
}

void VeryReal::SceneManager::Refresh() {
    auto it = scenes_list.begin();
    while (it != scenes_list.end()) {
        if ((*it)->GetToEliminate()) {
            it = RemoveScene(it);
        }
        else {
            ++it;
        }
    }
}

VeryReal::Scene* VeryReal::SceneManager::AddScene(scene_name name, bool active) {


    Scene* scene = new Scene();
    scene->SetName(name);
    scenes_list.push_back(scene);
    ActivationScene(name, active);
    EliminationScene(name, false);

    return scene;
}

std::list<VeryReal::Scene*>::iterator VeryReal::SceneManager::RemoveScene(std::list<VeryReal::Scene*>::iterator scene) {
    delete (*scene);
    return scenes_list.erase(scene);
}

void VeryReal::SceneManager::ActivationScene(scene_name name, bool active) {
    for (auto it : scenes_list)
        if (it->GetName() == name) it->SetActive(active);
}

void VeryReal::SceneManager::EliminationScene(scene_name name, bool to_eliminate) {
    for (auto it : scenes_list)
        if (it->GetName() == name) it->SetToEliminate(to_eliminate);
}

VeryReal::Scene* VeryReal::SceneManager::GetScene(scene_name name) {
    if (HasScene(name)) {
        for (auto c : scenes_list)
            if (c->GetName() == name) return c;

        return nullptr;
    }
    else
        return nullptr;
}

bool VeryReal::SceneManager::HasScene(scene_name name) {
    for (auto c : scenes_list)
        if (c->GetName() == name) return true;
    return false;
}

VeryReal::Scene* VeryReal::SceneManager::GetActiveScene() {
    for (auto it : scenes_list)
        if (it->GetActive()) return it;
}
