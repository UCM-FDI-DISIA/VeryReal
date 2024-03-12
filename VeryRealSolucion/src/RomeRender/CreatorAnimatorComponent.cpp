#include "CreatorAnimatorComponent.h"
#include "AnimatorComponent.h"
VeryReal::Component* VeryReal::CreatorAnimatorComponent::CreatorSpecificComponent() {
	return new VeryReal::AnimatorComponent();
}