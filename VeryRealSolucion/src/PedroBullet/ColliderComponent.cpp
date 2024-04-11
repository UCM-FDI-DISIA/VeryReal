#include "ColliderComponent.h"
#include <Entity.h>

void VeryReal::ColliderComponent::Init()
{

}
void VeryReal::ColliderComponent::OnCollisionEnter(Entity* entity)
{
	entity->OnCollisionEnter(entity);
}
void VeryReal::ColliderComponent::OnCollisionExit(Entity* entity)
{
	entity->OnCollisionExit(entity);
}
void VeryReal::ColliderComponent::OnCollisionStay(Entity* entity)
{
	entity->OnCollisionStay(entity);
}