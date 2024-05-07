#include "CreatorColliderComponent.h"
#include "ColliderComponent.h"
using namespace VeryReal;
Component* CreatorColliderComponent::CreatorSpecificComponent() {
	return new ColliderComponent();
}

 std::pair<bool, std::string> CreatorColliderComponent::SpecificInitComponent(Component* c) { return {true, "ColliderComponent initialized"}; }

 std::pair<bool, std::string> CreatorColliderComponent::SpecificInitComponentByCopy(Component* c, Component* other) {
     return {true, "ColliderComponent initialized"};
 }