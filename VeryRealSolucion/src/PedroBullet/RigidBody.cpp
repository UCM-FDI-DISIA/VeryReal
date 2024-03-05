#include "RigidBody.h"
#include "BulletDynamics/Dynamics/btRigidBody.h"
#include "PedroBullet.h"
#include "Entity.h"

#include <LinearMath/btDefaultMotionState.h>


#include <BulletDynamics/Dynamics/btDiscreteDynamicsWorld.h>  //gestion de colisiones, gravedad...
#include <BulletCollision/CollisionShapes/btSphereShape.h>
#include <BulletCollision/CollisionShapes/btCylinderShape.h>
#include <BulletCollision/CollisionShapes/btCapsuleShape.h>
#include <BulletCollision/CollisionDispatch/btDefaultCollisionConfiguration.h>
#include <BulletCollision/BroadphaseCollision/btDbvtBroadphase.h>
#include <BulletDynamics/ConstraintSolver/btSequentialImpulseConstraintSolver.h>



RigidBody::RigidBody(float mass, float friccion, float bounce, int mGroup, VeryReal::TransformComponent* transform, btCollisionShape* shape, PBMovementType mType, unordered_set<int>* mask)
{

    //btRigidBody::btRigidBodyConstructionInfo info{
    //    m_mass = mass;
    //    this->friccion = friccion;
    //    this->bounce = bounce;
    //    this->mGroup = mGroup;
    //    this->transform = transform;
    //    this->shape = shape;
    //    this->movementType = mType;
    //    this->mask = mask;
    //    this->SetName("rigidbody");
    //};


   
    btRigidBody::btRigidBodyConstructionInfo* constructionInfo = new btRigidBody::btRigidBodyConstructionInfo(mass, shape, btTransform({ 0, 0, 0, 0 }, {0,0,0}), btVector3{ 0,0,0 });
	this->mass = mass;
	this->friccion = friccion;
	this->bounce = bounce;
	this->mGroup = mGroup;
	this->transform = transform;
	this->shape = shape;
	this->movementType = mType;
	this->mask = mask;
	this->SetName("rigidbody");
   // bulletRigidBody = new btRigidBody(btRigidBody::btScalar(this->mass),this->shape, btMotionState*, this->movementType, btVector3( 0, 0, 0)); // temporal
                   


RigidBody::~RigidBody() {
    if (btRigidBody) {
        PedroBullet::Instance()->deleteRigidbody(btRigidBody); // Asegúrate de que esta función elimina correctamente el cuerpo rígido de Bullet.
        delete btRigidBody->getCollisionShape();
        delete btRigidBody->getMotionState();
        delete btRigidBody;
    }
}



void RigidBody::addToMask(int newGroup)
{
	this->mask->insert(newGroup);
}

void RigidBody::start()
{
	
	this->transform = this->GetEntity()->GetComponent<VeryReal::TransformComponent>("transform");
	if(!transform)
	{
		//error
		return;
	}

	//Nos quedamos hoy por aquí, tenemos que cambiar la rotacion de las entidades a V4 para poder pasarlas a Quaternions
	/*btQuaternion btQ(
	this->bulletTransform = new btTransform(btQuaternion(this->transform->GetRotation().));*/
}




void RigidBody::CreateBulletRigidBody() {
    btCollisionShape* collisionShape = nullptr;
    switch (shape) {
    case SHAPES_SPHERE:
        collisionShape = new btSphereShape(transform->GetScale().x); // Suponiendo que el scale.x representa el radio
        break;
    case SHAPES_BOX:
        collisionShape = new btBoxShape(btVector3(transform->GetScale().x, transform->GetScale().y, transform->GetScale().z));
        break;
    case SHAPES_CYLINDER:
        collisionShape = new btCylinderShape(btVector3(transform->GetScale().x, transform->GetScale().y, transform->GetScale().z));
        break;
    case SHAPES_CAPSULE:
        collisionShape = new btCapsuleShape(transform->GetScale().x, transform->GetScale().y); // Suponiendo que x es el radio y y es la altura
        break;
    }

    btVector3 localInertia(0, 0, 0);
    if (movementType != MOVEMENT_TYPE_STATIC) {
        collisionShape->calculateLocalInertia(mass, localInertia);
    }

    btTransform startTransform;
    startTransform.setIdentity();
    startTransform.setOrigin(btVector3(transform->GetPosition().x, transform->GetPosition().y, transform->GetPosition().z));
    // Convertir la rotación de Euler/quaternion a btQuaternion si es necesario

    btDefaultMotionState* motionState = new btDefaultMotionState(startTransform);
    btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, motionState, collisionShape, localInertia);
    rbInfo.m_friction = friction;
    rbInfo.m_restitution = restitution;

    btRigidBody = new btRigidBody(rbInfo);

    if (movementType == MOVEMENT_TYPE_KINEMATIC) {
        btRigidBody->setCollisionFlags(btRigidBody->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT);
        btRigidBody->setActivationState(DISABLE_DEACTIVATION);
    }

    PedroBullet::Instance()->addRigidbody(btRigidBody); // Asegúrate de que esta función añade correctamente el cuerpo rígido a Bullet.
}

void RigidBody::Update() {
    if (btRigidBody && btRigidBody->getMotionState()) {
        btTransform trans;
        btRigidBody->getMotionState()->getWorldTransform(trans);

        // Actualiza el componente de transformación de tu entidad con los datos de Bullet
        transform->SetPosition(glm::vec3(trans.getOrigin().getX(), trans.getOrigin().getY(), trans.getOrigin().getZ()));
        // Actualizar la rotación si es necesario
    }
}