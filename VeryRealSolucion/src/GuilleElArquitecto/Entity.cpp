#include "Entity.h"
Entity::Entity() {}
Entity::~Entity() {}


void Entity::RemoveComponent(component_name c_name) {
	if (HasComponent(c_name)) {
		delete components_map.at(c_name);
		components_map.erase(c_name);
	}
}


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