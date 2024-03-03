#pragma once


#ifndef RIGIDBODY
#define RIGIDBODY


#include "Component.h"
#include <unordered_set>

class btRigidBody;
class btTransform;
class btQuaternion;
class btCollisionShape;
class TransformComponent;

class RigidBody : public VeryReal::Component
{
public:

	RigidBody(float);

private:


	float mass;
	
	float fricion;
	
	float bounce;
	
	//Conjunto en el que tenemos las mascaras con las que el rB puede chocar
	unordered_set<int>mask;
	
	int mGroup;


	btRigidBody* btRigidBody = nullptr;
	btTransform* btTransform = nullptr;

	TransformComponent* transform = nullptr;

};

#endif