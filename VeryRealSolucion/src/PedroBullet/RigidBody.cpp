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
#include <LinearMath/btDefaultMotionState.h>

RigidBody::RigidBody(float mass, float friccion, float bounce, int mGroup, VeryReal::TransformComponent* transform, PBShapes shape, PBMovementType mType,unordered_set<int>* mask)
{
	this->mass = mass;
	this->friccion = friccion;
	this->bounce = bounce;
	this->mGroup = mGroup;
	this->transform = transform;
	this->shape = shape;
	this->movementType = mType;
	this->mask = mask;
	this->SetName("rigidbody");
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