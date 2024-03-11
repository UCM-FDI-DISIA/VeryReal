#include "RigidBodyComponent.h"
#include <BulletCollision/CollisionShapes/btBoxShape.h> // Asegúrate de incluir todos los tipos de formas que necesites
#include "TransformComponent.h"
#include <btBulletDynamicsCommon.h>
#include "Entity.h"
#include "Collider.h"

using namespace VeryReal;

RigidBodyComponent::RigidBodyComponent(PBShapes shapeType, float mass, float friction, float restitution, PBMovementType movementType, bool trigger)
    : mass(mass), friction(friction), restitution(restitution), movementType(movementType) {
    InitializeRigidBody(shapeType);
 
    collider = this->GetEntity()->GetComponent<Collider>("collider");
    if (trigger)
    {
        collider->SetActive(false);
    }

    if(!collider)
    {
        //ERROR
        return;
    }
    this->GetBulletRigidBody()->setUserPointer(collider);
}

RigidBodyComponent::~RigidBodyComponent() {

}

void RigidBodyComponent::InitializeRigidBody(PBShapes shapeType) {
    transformComponent = this->GetEntity()->GetComponent<TransformComponent>("transform");
;
    collisionShape.reset(CreateCollisionShape(shapeType));
    
    btVector3 localInertia(0, 0, 0);
    if (mass != 0.0f) {
        collisionShape->calculateLocalInertia(mass, localInertia);
    }

    Vector3 pos = transformComponent->GetPosition();
    btTransform startTransform;
    startTransform.setIdentity();
    startTransform.setOrigin(btVector3(pos.GetX(), pos.GetY(), pos.GetZ()));

    motionState.reset(new btDefaultMotionState(startTransform));
    btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, motionState.get(), collisionShape.get(), localInertia);
    rbInfo.m_restitution = restitution;
    rbInfo.m_friction = friction;

    rigidBody.reset(new btRigidBody(rbInfo));
}

btCollisionShape* RigidBodyComponent::CreateCollisionShape(PBShapes shapeType) {
    switch (shapeType) {
    case SHAPES_BOX:
        return new btBoxShape(btVector3(1, 1, 1)); 

    default:
        return nullptr;
    }
}

void RigidBodyComponent::SetVelocityLinear(const Vector3& velocity) {
    rigidBody->setLinearVelocity(btVector3(velocity.GetX(), velocity.GetY(), velocity.GetZ()));
}
void RigidBodyComponent::SetVelocityAngular(const Vector3& velocity) {
    rigidBody->setAngularVelocity(btVector3(velocity.GetX(), velocity.GetY(), velocity.GetZ()));
}

Vector3 RigidBodyComponent::GetVelocity() const {
    btVector3 vel = rigidBody->getLinearVelocity();
    return Vector3(vel.x(), vel.y(), vel.z());
}

void RigidBodyComponent::AddImpulse(const Vector3& impulse){

    rigidBody->applyCentralImpulse(btVector3(impulse.GetX(), impulse.GetY(), impulse.GetZ()));
}

void RigidBodyComponent::AddTorque(const Vector3& torque){

    rigidBody->applyCentralImpulse(btVector3(torque.GetX(), torque.GetY(), torque.GetZ()));
}

void RigidBodyComponent::SetActiveRB(bool b) {
    isActive = b;
}

void RigidBodyComponent::SetActiveTrigger(bool b) {
    isTrigger = b;
    if(b)
        collider->SetActive(false);
    else collider->SetActive(true);
}

bool RigidBodyComponent::GetActiveRB() {
    return isActive;
}

bool RigidBodyComponent::GetActiveTrigger() {
    return isTrigger;
    //return !collider->GetActive();

}

btRigidBody* RigidBodyComponent::GetBulletRigidBody() const {
    return rigidBody.get();
}
