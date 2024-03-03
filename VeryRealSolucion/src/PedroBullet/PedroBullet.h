#ifndef PEDROBULLET
#define PEDROBULLET
#pragma once

#include <vector>
#include "Singleton.h"
#include <Manager.h>
#include <array>

using namespace std;




class btDiscreteDynamicsWorld;
class btCollisionConfiguration;
class btCollisionDispatcher;
class btBroadphaseInterface;
class btSequentialImpulseConstraintSolver;
class btRigidBody;
class btTransform;

class PedroBullet : public VeryReal::Manager<PedroBullet> {
    friend Singleton<PedroBullet>;

public:
    virtual ~PedroBullet() {}
    virtual void Init();
    virtual void Update(const double& timeStep);        //de momento pasaremos solo el dt, pero sabemos que hay dos variables mas.
  
    //Nos quedamos aquí, esta funcion la llamaran los Rb para crearse.
    void createRigidBody(btTransform* transform);
    void deleteRigidbody(btRigidBody* rB);
private:
    PedroBullet() {};

    void addRigidbody(btRigidBody* rB);


    btDiscreteDynamicsWorld* dynamicWorld;
    btCollisionConfiguration* collisionConfig;
    btCollisionDispatcher* collisionDispatcher;
    btBroadphaseInterface* interface;
    btSequentialImpulseConstraintSolver* constraintSolver;

    
};

/// Singleton instance
/// @return A pointer of the instance
inline PedroBullet& PB() {
    return *PedroBullet::Instance();
}
#endif // !PEDROBULLET