#include "RigidBody.h"
#include <BulletCollision/CollisionShapes/btBoxShape.h> // Asegúrate de incluir todos los tipos de formas que necesites

using namespace VeryReal;

RigidBodyComponent::RigidBodyComponent(TransformComponent* transform, PBShapes shapeType, float mass, float friction, float restitution, PBMovementType movementType)
    : transformComponent(transform), mass(mass), friction(friction), restitution(restitution), movementType(movementType) {
    InitializeRigidBody(shapeType);
}

RigidBodyComponent::~RigidBodyComponent() {

}

void RigidBodyComponent::InitializeRigidBody(PBShapes shapeType) {
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

void RigidBodyComponent::SetVelocity(const Vector3& velocity) {
    rigidBody->setLinearVelocity(btVector3(velocity.GetX(), velocity.GetY(), velocity.GetZ()));
}

Vector3 RigidBodyComponent::GetVelocity() const {
    btVector3 vel = rigidBody->getLinearVelocity();
    return Vector3(vel.x(), vel.y(), vel.z());
}



btRigidBody* RigidBodyComponent::GetBulletRigidBody() const {
    return rigidBody.get();
}
