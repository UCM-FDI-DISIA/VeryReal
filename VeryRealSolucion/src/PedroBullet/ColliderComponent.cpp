#include "ColliderComponent.h"
#include <Entity.h>

void VeryReal::ColliderComponent::Init()
{

}
void VeryReal::ColliderComponent::OnCollisionEnter(Entity* entity){ this->GetEntity()->OnCollisionEnter(entity); }
void VeryReal::ColliderComponent::OnCollisionExit(Entity* entity){ this->GetEntity()->OnCollisionExit(entity); }
void VeryReal::ColliderComponent::OnCollisionStay(Entity* entity){ this->GetEntity()->OnCollisionStay(entity); }