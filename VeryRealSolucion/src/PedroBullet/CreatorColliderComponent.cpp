#include "CreatorColliderComponent.h"
#include "ColliderComponent.h"
using namespace VeryReal;
Component* CreatorColliderComponent::CreatorSpecificComponent() {
	return new ColliderComponent();
}

void CreatorColliderComponent::SpecificInitComponent(Component* c) {
	// Asignar parametros y mas cosas del init
}

void CreatorColliderComponent::SpecificInitComponentByCopy(Component* c, Component* other) {
    // Asignar parametros y mas cosas del init por copia
}