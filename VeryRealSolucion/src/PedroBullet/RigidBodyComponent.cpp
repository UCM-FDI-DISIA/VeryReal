#include "RigidBodyComponent.h"
#include <BulletCollision/CollisionShapes/btBoxShape.h> // Asegúrate de incluir todos los tipos de formas que necesites
#include "TransformComponent.h"
#include <btBulletDynamicsCommon.h>
#include "Entity.h"
#include "ColliderComponent.h"

using namespace VeryReal;

RigidBodyComponent::RigidBodyComponent()
    : mass(0), friction(0), restitution(0), movementType(MOVEMENT_TYPE_DYNAMIC), isTrigger(false) {
    
}
bool RigidBodyComponent::InitComponent(int shapeType, float mass, float friction, float restitution, int movementType, bool trigger) {
   // this->shapeType = shapeType;
    this->mass = mass;
    this->friction = friction;
    this->restitution = restitution;
    this->movementType = (PBMovementType)movementType;
    this-> isTrigger = trigger;
    return InitializeRigidBody((PBShapes)shapeType, this->movementType, trigger);
}
RigidBodyComponent::~RigidBodyComponent() {

}

bool RigidBodyComponent::InitializeRigidBody(PBShapes shapeType, PBMovementType movementType, bool trigger) {
    transformComponent = this->GetEntity()->GetComponent<TransformComponent>("TransformComponent");
    if (transformComponent == nullptr) {
        #ifdef DEBUG_MODE
                // Código específico para modo de depuración
        cerr << BEDUG_ERROR_TRANSFORM;
        #endif
        return false;
    }

    delete collisionShape;
    collisionShape = CreateCollisionShape(shapeType);
    //collisionShape.reset(CreateCollisionShape(shapeType));
    
    btVector3 localInertia(0, 0, 0);
    if (mass != 0.0f) {
        collisionShape->calculateLocalInertia(mass, localInertia);
    }

    Vector3 pos = transformComponent->GetPosition();
    btTransform startTransform;
    startTransform.setIdentity();
    startTransform.setOrigin(btVector3(pos.GetX(), pos.GetY(), pos.GetZ()));

    motionState.reset(new btDefaultMotionState(startTransform));
    btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, motionState.get(), collisionShape, localInertia); //
    rbInfo.m_restitution = restitution;
    rbInfo.m_friction = friction;

    rigidBody = new btRigidBody(rbInfo);

    //Inicializar el componente colider
    collider = this->GetEntity()->GetComponent<ColliderComponent>("collider");

    if (!collider)
    {
        //ERROR
        return false;
    }
    this->GetBulletRigidBody()->setUserPointer(collider);

    //Determinar el movement type
    SetMovementType(movementType);

    //Hacerlo trigger si es trigger
    if (trigger)
    {
        rigidBody->setCollisionFlags(rigidBody->getCollisionFlags() | btCollisionObject::CF_NO_CONTACT_RESPONSE);
    }

    return true;
}
btRigidBody* RigidBodyComponent::GetBulletRigidBody() 
{
    return this->rigidBody;
}

btCollisionShape* RigidBodyComponent::GetCollisionShape() { 
    return collisionShape;
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

    rigidBody->applyTorqueImpulse(btVector3(torque.GetX(), torque.GetY(), torque.GetZ()));// poner una de las tres..........................
}

void RigidBodyComponent::SetActiveTrigger(bool b) {
    if(b)
        rigidBody->setCollisionFlags(rigidBody->getCollisionFlags() | btCollisionObject::CF_NO_CONTACT_RESPONSE);
    else    rigidBody->setCollisionFlags(rigidBody->getCollisionFlags() & ~btCollisionObject::CF_NO_CONTACT_RESPONSE);

}

bool RigidBodyComponent::GetActiveTrigger() {
    if (rigidBody->getCollisionFlags() == 4)
        return true;
    else return false;
}

void VeryReal::RigidBodyComponent::SetMass(float n)
{
    mass = n;
}

float VeryReal::RigidBodyComponent::GetMass()
{
    return mass;
}

void VeryReal::RigidBodyComponent::SetFriction(float n)
{
    friction = n;
}

float VeryReal::RigidBodyComponent::GetFriction()
{
    return friction;
}

void VeryReal::RigidBodyComponent::SetRestitution(float n)
{
    restitution = n;
}

float VeryReal::RigidBodyComponent::GetRestitution()
{
    return restitution;
}

void VeryReal::RigidBodyComponent::SetMovementType(PBMovementType mT)
{
    if(mT == MOVEMENT_TYPE_DYNAMIC)
        rigidBody->setCollisionFlags(rigidBody->getCollisionFlags() | btCollisionObject::CF_DYNAMIC_OBJECT);
    if (mT == MOVEMENT_TYPE_STATIC)
        rigidBody->setCollisionFlags(rigidBody->getCollisionFlags() | btCollisionObject::CF_STATIC_OBJECT);
    if (mT == MOVEMENT_TYPE_KINEMATIC)
        rigidBody->setCollisionFlags(rigidBody->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT);
}


