#include "Creator.h"
#include "Entity.h"

VeryReal::Creator::~Creator() {
	for (auto& c : creators_map)delete c.second;
	creators_map.clear();
}

void VeryReal::Creator::AddCreator(const creator_name& c_name, CreatorComponent* cretorcomponent) {
	RemoveCreator(c_name);
	creators_map.insert({ c_name,cretorcomponent });
}

void VeryReal::Creator::RemoveCreator(creator_name c_name) {
	if (HasCreator(c_name)) {
		delete creators_map.at(c_name);
		creators_map.erase(c_name);
	}
}

void VeryReal::Creator::AddPrefab(prefab_name p_name, Entity* ent) {
    RemovePrefab(p_name);
    prefabs_map.insert({p_name, ent});
}

void VeryReal::Creator::RemovePrefab(prefab_name p_name) {
    if (HasPrefab(p_name)) {
        delete prefabs_map.at(p_name);
        prefabs_map.erase(p_name);
    }
}

bool VeryReal::Creator::HasPrefab(prefab_name p_name) { 
    return prefabs_map.count(p_name);
}

//Devuelve el creator especifico y si no esta devuelve nullptr
VeryReal::Entity* VeryReal::Creator::GetPrefab(prefab_name p_name) {
    if (!HasPrefab(p_name)) {
        return nullptr;
    }
    return prefabs_map.at(p_name);
}