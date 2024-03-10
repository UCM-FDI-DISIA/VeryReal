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

    // Métodos para ayudar a la creación de cuerpos rígidos
    btRigidBody* CreateGround();
    btRigidBody* CreateFallingObject();
};

