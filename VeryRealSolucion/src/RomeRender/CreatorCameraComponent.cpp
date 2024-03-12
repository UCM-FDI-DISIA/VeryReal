#include "CreatorCameraComponent.h"
#include "CameraComponent.h"
VeryReal::Component* VeryReal::CreatorCameraComponent::CreatorSpecificComponent() {
	return new VeryReal::CameraComponent();
}