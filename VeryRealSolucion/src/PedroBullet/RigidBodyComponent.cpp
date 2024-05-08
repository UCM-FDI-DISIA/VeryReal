#include "RigidBodyComponent.h"
#include "TransformComponent.h"
#include <btBulletDynamicsCommon.h>
#include "Entity.h"
#include "ColliderComponent.h"
#include "PhysicsManager.h"

using namespace VeryReal;

RigidBodyComponent::RigidBodyComponent() : mass(0), friction(0), restitution(0), movementType(MOVEMENT_TYPE_DYNAMIC), isTrigger(false) { }

std::pair<bool, std::string> RigidBodyComponent::InitComponent(int shapeType, float mass, float friction, float restitution, int movementType,
                                                               bool trigger, Vector3 size,
                                       int mask, int group) {
    this->shape_type_var = shapeType;
    this->mass = mass;
    this->friction = friction;
    this->restitution = restitution;
    this->movementType = (PBMovementType)movementType;
    this->isTrigger = trigger;
    this->size_var = size;
    return InitializeRigidBody((PBShapes)shapeType, this->movementType, trigger, size, mask, group);
}

RigidBodyComponent::~RigidBodyComponent() {
    transformComponent = nullptr;
    collider = nullptr;
    delete collider;
    delete collisionShape;
    rigidBody->setMotionState(nullptr);
    VeryReal::PhysicsManager::Instance()->DeleteRigidBody(rigidBody);
    delete rigidBody;
}

std::pair<bool, std::string> RigidBodyComponent::InitializeRigidBody(PBShapes shapeType, PBMovementType movementType, bool trigger, Vector3 s, int m,
                                                                     int g) {
    transformComponent = this->GetEntity()->GetComponent<TransformComponent>();
    if (transformComponent == nullptr) {
        return {false, "There is no TransformComponent attached to the RigidBodyComponent"};
    }


    collisionShape = CreateCollisionShape(shapeType, s);
    btVector3 localInertia(0, 0, 0);
    if (mass != 0.0f) {
        collisionShape->calculateLocalInertia(mass, localInertia);
    }

    Vector3 pos = transformComponent->GetPosition();
    btTransform startTransform;
    startTransform.setIdentity();
    startTransform.setOrigin(btVector3(pos.GetX(), pos.GetY(), pos.GetZ()));
    startTransform.setRotation(btQuaternion(transformComponent->GetRotation().GetX(), transformComponent->GetRotation().GetY(),
                                            transformComponent->GetRotation().GetZ(), transformComponent->GetRotation().GetW()));
    motionState.reset(new btDefaultMotionState(startTransform));
    btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, motionState.get(), collisionShape, localInertia);
    rbInfo.m_restitution = restitution;
    rbInfo.m_friction = friction;

    rigidBody = new btRigidBody(rbInfo);

    //Inicializar el componente colider
    collider = this->GetEntity()->GetComponent<ColliderComponent>();
    if (!collider) {
#ifdef _DEBUG
        std::cout << "No se ha incluido collider, la comprobacion de las colisiones se omitira" << std::endl;
#endif   // DEBUG
    }
    rigidBody->setUserPointer(this);

    //Determinar el movement type
    SetMovementType(movementType);

    //Hacerlo trigger si es trigger
    if (trigger) {
        rigidBody->setCollisionFlags(rigidBody->getCollisionFlags() | btCollisionObject::CF_NO_CONTACT_RESPONSE);
    }

    VeryReal::PhysicsManager::Instance()->AddRigidBody(rigidBody);

    btBroadphaseProxy* bdProxy = rigidBody->getBroadphaseProxy();
    if (bdProxy == nullptr) {
        return {false, "Error: Broadphase proxy is null after adding the body to the world."};
    }

    //Mascaras y grupos de colision
    setMask(m);
    setGroup(g);
    return {true, "RigidBody was succesfully initialized"};
}

btRigidBody* RigidBodyComponent::GetBulletRigidBody() { return this->rigidBody; }

btCollisionShape* RigidBodyComponent::GetCollisionShape() { return collisionShape; }


void VeryReal::RigidBodyComponent::setMask(const int n) {
    if (rigidBody != nullptr) {
        mask = n;

        btBroadphaseProxy* bdProxy = rigidBody->getBroadphaseProxy();
        if (bdProxy != nullptr) bdProxy->m_collisionFilterMask = n;
    }
}

int VeryReal::RigidBodyComponent::getMask() const { return mask; }


void VeryReal::RigidBodyComponent::setGroup(const int n) {
    if (rigidBody != nullptr) {
        group = n;
        btBroadphaseProxy* bdProxy = rigidBody->getBroadphaseProxy();
        if (bdProxy != nullptr) bdProxy->m_collisionFilterGroup = n;
    }
}

int VeryReal::RigidBodyComponent::getGroup() const { return group; }

void RigidBodyComponent::Update(const double& dt) {
    if (movementType == MOVEMENT_TYPE_DYNAMIC) {
        // Establecer la posición actual del transformComponent usando la posición del objeto físico
        transformComponent->SetPosition(Vector3(rigidBody->getWorldTransform().getOrigin().getX(), rigidBody->getWorldTransform().getOrigin().getY(),
                                                rigidBody->getWorldTransform().getOrigin().getZ()));

        transformComponent->SetRotation(Vector4(rigidBody->getWorldTransform().getRotation().getX(), 
                                                rigidBody->getWorldTransform().getRotation().getY(),
                                                rigidBody->getWorldTransform().getRotation().getZ(), 
                                                rigidBody->getWorldTransform().getRotation().getW()));
        // Establecer la velocidad actual del transformComponent usando la velocidad lineal del objeto físico
        transformComponent->SetVelocity(Vector3(rigidBody->getLinearVelocity().getX(), 
                                                rigidBody->getLinearVelocity().getY(), 
                                                rigidBody->getLinearVelocity().getZ()));
    }
}

//La x es el radio en las esferas, cilindros y capsulas y la y la altura
btCollisionShape* RigidBodyComponent::CreateCollisionShape(PBShapes shapeType, Vector3 s) {
    switch (shapeType) {
    case SHAPES_BOX : return new btBoxShape(btVector3(s.GetX(), s.GetY(), s.GetZ())); break;
    case SHAPES_SPHERE : return new btSphereShape(btScalar(s.GetX())); break;
    case SHAPES_CYLINDER : return new btCylinderShape(btVector3(s.GetX(), s.GetY(), s.GetZ())); break;
    case SHAPES_CAPSULE : return new btCapsuleShape(btScalar(s.GetX()), btScalar(s.GetY())); break;
    default : return nullptr;
    }
}

void RigidBodyComponent::SetPosition(const Vector3& position) {
    rigidBody->getWorldTransform().setOrigin({position.GetX(), position.GetY(), position.GetZ()});
}

Vector3 RigidBodyComponent::GetPosition() const {
    btVector3 pos = rigidBody->getWorldTransform().getOrigin();
    return Vector3(pos.x(), pos.y(), pos.z());
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

void VeryReal::RigidBodyComponent::SetRotation(const VeryReal::Vector4& rotation) {
    rigidBody->getWorldTransform().setRotation(btQuaternion(rotation.GetX(), rotation.GetY(), rotation.GetZ(), rotation.GetW()));
}

void VeryReal::RigidBodyComponent::Rotate(const Vector3& axis, int degrees) {
    float radians = (float)(degrees * (M_PI / 180.0));
    float fHalfAngle(0.5f * radians);
    float fSin = sin(fHalfAngle);

    // Calcular el cuaternión de rotación
    btQuaternion rotationQuat(fSin * axis.GetX(), fSin * axis.GetY(), fSin * axis.GetZ(), cos(fHalfAngle));

    // Obtener el cuaternión actual del objeto
    btTransform currentTransform = rigidBody->getWorldTransform();
    btQuaternion currentRotation = currentTransform.getRotation();

    // Aplicar la rotación
    btQuaternion newRotation = rotationQuat * currentRotation;
    currentTransform.setRotation(newRotation);

    // Establecer la nueva transformación en el objeto
    rigidBody->setWorldTransform(currentTransform);
}

VeryReal::Vector4 VeryReal::RigidBodyComponent::GetRotation() {
    return Vector4(rigidBody->getWorldTransform().getRotation().getX(), rigidBody->getWorldTransform().getRotation().getY(),
                   rigidBody->getWorldTransform().getRotation().getZ(), rigidBody->getWorldTransform().getRotation().getW());
}


void RigidBodyComponent::AddImpulse(const Vector3& impulse) {
    rigidBody->applyCentralImpulse(btVector3(impulse.GetX(), impulse.GetY(), impulse.GetZ()));
}

void RigidBodyComponent::AddTorque(const Vector3& torque) {

    rigidBody->applyTorqueImpulse(btVector3(torque.GetX(), torque.GetY(), torque.GetZ()));   
}

void RigidBodyComponent::SetActiveTrigger(bool b) {
    if (b) rigidBody->setCollisionFlags(rigidBody->getCollisionFlags() | btCollisionObject::CF_NO_CONTACT_RESPONSE);
    else
        rigidBody->setCollisionFlags(rigidBody->getCollisionFlags() & ~btCollisionObject::CF_NO_CONTACT_RESPONSE);
}

bool RigidBodyComponent::GetActiveTrigger() {
    if (rigidBody->getCollisionFlags() == 4) return true;
    else
        return false;
}

void VeryReal::RigidBodyComponent::SetMass(float n) { mass = n; }

float VeryReal::RigidBodyComponent::GetMass() { return mass; }

void VeryReal::RigidBodyComponent::SetFriction(float n) { friction = n; }

float VeryReal::RigidBodyComponent::GetFriction() { return friction; }

void VeryReal::RigidBodyComponent::SetRestitution(float n) { restitution = n; }

float VeryReal::RigidBodyComponent::GetRestitution() { return restitution; }

void VeryReal::RigidBodyComponent::SetMovementType(PBMovementType mT) {
    if (mT == MOVEMENT_TYPE_DYNAMIC) 
    {
        rigidBody->setAngularFactor(btVector3(0, 0, 0));
        rigidBody->setActivationState(4);
        rigidBody->setCollisionFlags(rigidBody->getCollisionFlags() | btCollisionObject::CF_DYNAMIC_OBJECT);
    }
    if (mT == MOVEMENT_TYPE_STATIC) 
    {

        rigidBody->setAngularFactor(btVector3(0, 0, 0));
        rigidBody->setLinearFactor(btVector3(0, 0, 0));
        rigidBody->setCollisionFlags(rigidBody->getCollisionFlags() | btCollisionObject::CF_STATIC_OBJECT);
    }
    if (mT == MOVEMENT_TYPE_KINEMATIC) rigidBody->setCollisionFlags(rigidBody->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT);
    movementType = mT;
}

