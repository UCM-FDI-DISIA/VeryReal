#include "Entity.h"
#include "Component.h"
VeryReal::Entity::Entity() : is_alive(true) {}
VeryReal::Entity::~Entity() {
    for (auto c : components_map) {
        delete (c.second);
    }
}

void VeryReal::Entity::RemoveComponent(component_name c_name) {
	if (HasComponent(c_name)) {
		delete components_map.at(c_name);
		components_map.erase(c_name);
	}
}
void VeryReal::Entity::Update(const double& dt) {
	for (auto c : components_map) {
		if (c.second->GetActive()) {
			c.second->Update(dt);
		}
		else {
			components_list_removed.push_back(c.first);
		}
	}
	Refresh();
}
void VeryReal::Entity::Refresh() {
	for (auto c = components_list_removed.begin(); c != components_list_removed.end();) {
		RemoveComponent(*c);
		auto p = c;
		p++;
		components_list_removed.pop_front();
		c = p;
	}
}
void VeryReal::Entity::OnCollisionEnter(Entity* other) 
{
	for(auto& c :components_map)
	{
		if(c.second->GetActive() && c.first != "ColliderComponent")
			c.second->OnCollisionEnter(other);
	}
}
void VeryReal::Entity::OnCollisionExit(Entity* other)
{
	for (auto& c : components_map)
	{
		if (c.second->GetActive() && c.first != "ColliderComponent")
			c.second->OnCollisionExit(other);
	}
}
void VeryReal::Entity::OnCollisionStay(Entity* other)
{
	for (auto& c : components_map)
	{
		if (c.second->GetActive() && c.first != "ColliderComponent")
			c.second->OnCollisionStay(other);
	}
}