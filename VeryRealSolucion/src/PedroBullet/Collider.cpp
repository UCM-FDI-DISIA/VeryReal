#include "Collider.h"
#include <Entity.h>

void VeryReal::Collider::onCollisionEnter(Entity* entity)
{
	entity->onCollisionEnter(entity);
}
void VeryReal::Collider::onCollisionExit(Entity* entity)
{
	entity->onCollisionExit(entity);
}
void VeryReal::Collider::onCollisionStay(Entity* entity)
{
	entity->onCollisionStay(entity);
}