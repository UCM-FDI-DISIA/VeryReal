#include "CreatorAnimatorComponent.h"
#include "Animator.h"
VeryReal::Component* VeryReal::CreatorAnimatorComponent::CreatorSpecificComponent() {
	return new VeryReal::Animator();
}