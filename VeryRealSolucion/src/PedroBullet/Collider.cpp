#include "Collider.h"
#include <Entity.h>



void VeryReal::Collider::Init()
{

}
void VeryReal::Collider::OnCollisionEnter(Entity* entity)
{
	entity->OnCollisionEnter(entity);
}
void VeryReal::Collider::OnCollisionExit(Entity* entity)
{
	entity->OnCollisionExit(entity);
}
void VeryReal::Collider::OnCollisionStay(Entity* entity)
{
	entity->OnCollisionStay(entity);
}