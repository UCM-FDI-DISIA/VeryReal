#include "CreatorTransformComponent.h"
#include "TransformComponent.h"
VeryReal::CreatorTransformComponent::CreatorTransformComponent() {

}
VeryReal::CreatorTransformComponent::~CreatorTransformComponent() {

}
VeryReal::Component* VeryReal::CreatorTransformComponent::CreatorSpecificComponent() {
	TransformComponent* t = new TransformComponent();
	return t;
}