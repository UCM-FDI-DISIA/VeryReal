#pragma once


#ifndef RIGIDBODY
#define RIGIDBODY

#include "Component.h"
#include <unordered_set>
#include "PhysicsValues.h"
#include "TransformComponent.h"
#include "BulletDynamics/Dynamics/btRigidBody.h"

class btRigidBody;
class btTransform;
class btQuaternion;
class btCollisionShape;


class RigidBody : public VeryReal::Component
{
public:

	RigidBody(float mass, float friccion, float bounce,int mGroup,VeryReal::TransformComponent* transform, btCollisionShape* shape, PBMovementType mType,unordered_set<int>* mask);
	void addToMask(int newGroup);
	void start();
	virtual ~RigidBody() {}
private:
	
	//~RigidBody();

	btCollisionShape* shape;
	PBMovementType movementType;

	bool isTrigger = false;

	float mass;
	
	float friccion;
	
	float bounce;
	
	//Conjunto en el que tenemos las mascaras con las que el rB puede chocar
	unordered_set<int>* mask;
	
	int mGroup;


	btRigidBody* bulletRigidBody = nullptr;
	btTransform* bulletTransform = nullptr;

	VeryReal::TransformComponent* transform = nullptr;

};

#endif