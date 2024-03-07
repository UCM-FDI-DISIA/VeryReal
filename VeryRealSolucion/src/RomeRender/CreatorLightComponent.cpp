#include "CreatorLightComponent.h"
#include "Light.h"
VeryReal::Component* VeryReal::CreatorLightComponent::CreatorSpecificComponent() {
	return new VeryReal::Light();
}