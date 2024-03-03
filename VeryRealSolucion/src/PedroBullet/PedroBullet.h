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

private:
    btDiscreteDynamicsWorld* dynamicWorld;
    btCollisionConfiguration* collisionConfig;
    btCollisionDispatcher* collisionDispatcher;
    btBroadphaseInterface* broadphase;
    btSequentialImpulseConstraintSolver* solver;

protected:
    PedroBullet();


public:
    void Init();
    void Update(float deltaTime);
    void Cleanup();
    virtual ~PedroBullet();
    void AddRigidBody(btRigidBody* body);
    void RemoveRigidBody(btRigidBody* body);
};


/// Singleton instance
/// @return A pointer of the instance
inline PedroBullet& PB() {
    return *PedroBullet::Instance();
}
#endif // !PEDROBULLET