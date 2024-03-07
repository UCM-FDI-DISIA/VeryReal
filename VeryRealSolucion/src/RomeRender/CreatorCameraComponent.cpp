#include "CreatorCameraComponent.h"
#include "Camera.h"
VeryReal::Component* VeryReal::CreatorCameraComponent::CreatorSpecificComponent() {
	return new VeryReal::Camara();
}