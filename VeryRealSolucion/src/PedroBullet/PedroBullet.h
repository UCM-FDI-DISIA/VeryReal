#ifndef PEDROBULLET
#define PEDROBULLET
#pragma once

#include <vector>
#include "Singleton.h"
#include <Manager.h>
#include <array>
#include "Vector3.h"

using namespace std;

class btDiscreteDynamicsWorld;
class btCollisionConfiguration;
class btCollisionDispatcher;
class btBroadphaseInterface;
class btSequentialImpulseConstraintSolver;
class btRigidBody;
class btTransform;
class btVector3;

enum PBShapes;
enum PBMovementType;
class VeryReal::RigidBodyComponent;

class PedroBullet : public VeryReal::Manager<PedroBullet> {

    friend Singleton<PedroBullet>;
private:
    btDiscreteDynamicsWorld* dynamicWorld;
    btCollisionConfiguration* collisionConfig;
    btCollisionDispatcher* collisionDispatcher;
    btBroadphaseInterface* broadphase;
    btSequentialImpulseConstraintSolver* solver;

    //vector<VeryReal::RigidBodyComponent*> rigidbodies;
    vector<VeryReal::RigidBodyComponent*> rigidbodies;


protected:
    PedroBullet();


public:
    virtual void Init();
    virtual void Update(float deltaTime);
    virtual ~PedroBullet();
    void createGround(); //Inicializar el mundo de físicas

    void AddRigidBody(PBShapes shapeType, float mass, float friction, float restitution, PBMovementType movementType);    
    //void RemoveRigidBody(VeryReal::RigidBodyComponent* body);

    void addForce(btRigidBody* body, btVector3 force);
    void Cleanup();
    //vector conversion for bullet
    btVector3 V3ToBtV3(VeryReal::Vector3 conversion) const;

};

/// Singleton instance
/// @return A pointer of the instance
inline PedroBullet& PB() {
    return *PedroBullet::Instance();
}
#endif // !PEDROBULLET