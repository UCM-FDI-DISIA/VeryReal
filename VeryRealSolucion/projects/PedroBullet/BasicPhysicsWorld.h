#pragma once

#include <btBulletDynamicsCommon.h>

class BasicPhysicsWorld {
public:
    BasicPhysicsWorld();
    ~BasicPhysicsWorld();

    void InitializeWorld();
    void Update(float deltaTime);
    void Cleanup();

private:
    btDiscreteDynamicsWorld* dynamicsWorld;
    btRigidBody* groundBody;
    btRigidBody* fallingBody;

    // M�todos para ayudar a la creaci�n de cuerpos r�gidos
    btRigidBody* CreateGround();
    btRigidBody* CreateFallingObject();
};

