#include "CreatorColliderComponent.h"
#include "ColliderComponent.h"
using namespace VeryReal;
Component* CreatorColliderComponent::CreatorSpecificComponent() {
	Component* c = new ColliderComponent();
	return c;
}