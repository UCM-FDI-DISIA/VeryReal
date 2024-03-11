#include "CreatorColliderComponent.h"
#include "Collider.h"
using namespace VeryReal;
Component* CreatorColliderComponent::CreatorSpecificComponent() {
	Component* c = new Collider();
}