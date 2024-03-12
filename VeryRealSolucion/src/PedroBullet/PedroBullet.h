#ifndef PEDROBULLET
#define PEDROBULLET
#pragma once

#include <vector>
#include "Singleton.h"
#include <Manager.h>
#include <array>
#include "Vector3.h"



class btDiscreteDynamicsWorld;
class btCollisionConfiguration;
class btCollisionDispatcher;
class btBroadphaseInterface;
class btSequentialImpulseConstraintSolver;
class btRigidBody;
class btTransform;
class btVector3;
class btPersistentManifold;

enum PBShapes;
enum PBMovementType;
class RigidBodyComponent;
class ColliderComponent;

class PedroBullet : public VeryReal::Manager<PedroBullet> {

    friend Singleton<PedroBullet>;
private:
    btDiscreteDynamicsWorld* dynamicWorld;
    btCollisionConfiguration* collisionConfig;
    btCollisionDispatcher* collisionDispatcher;
    btBroadphaseInterface* broadphase;
    btSequentialImpulseConstraintSolver* solver;
   /* svector<RigidBodyComponent*> rigidbodies;*/


protected:
    PedroBullet();


public:

    virtual void Init();
    virtual void Update(float deltaTime);
    virtual ~PedroBullet();
    void createGround(); //Inicializar el mundo de f�sicas

    void AddRigidBody(PBShapes shapeType, float mass, float friction, float restitution, PBMovementType movementType);    

    void addForce(btRigidBody* body, btVector3 force);
    void Cleanup();
    //conversi�n al vector de bullet
    btVector3 V3ToBtV3(VeryReal::Vector3 conversion) const;


   
};

/// Singleton instance
/// @return A pointer of the instance
inline PedroBullet& PB() {
    return *PedroBullet::Instance();
}
#endif // !PEDROBULLET