#include "Entity.h"
Entity::Entity() {

}
Entity::~Entity() {

}

void Entity::RemoveComponent(component_name c_name) {
	if (components_map.find(c_name) != components_map.end()) {
		components_map.erase(c_name);
	}
}
void Entity::Update() {
	for (auto c : components_map) c.second->Update();
}