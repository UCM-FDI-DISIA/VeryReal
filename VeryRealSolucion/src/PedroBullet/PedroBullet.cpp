#include "PedroBullet.h"

#include <iostream>
#include <BulletDynamics/Dynamics/btDiscreteDynamicsWorld.h>  //gestion de colisiones, gravedad...
#include <BulletCollision/CollisionShapes/btSphereShape.h>
#include <BulletCollision/CollisionShapes/btCylinderShape.h>
#include <BulletCollision/CollisionShapes/btCapsuleShape.h>
#include <BulletCollision/CollisionDispatch/btDefaultCollisionConfiguration.h>
#include <BulletCollision/BroadphaseCollision/btDbvtBroadphase.h>
#include <BulletDynamics/ConstraintSolver/btSequentialImpulseConstraintSolver.h>
#include <LinearMath/btDefaultMotionState.h>
#include <LinearMath/btVector3.h>
#include "RigidBodyComponent.h"
#include "PhysicsValues.h"
// Constructor
PedroBullet::PedroBullet() :
    dynamicWorld(nullptr),
    collisionConfig(nullptr),
    collisionDispatcher(nullptr),
    broadphase(nullptr),
    solver(nullptr) {
}

// Destructor
PedroBullet::~PedroBullet() {
    delete dynamicWorld;
    delete solver;
    delete broadphase;
    delete collisionDispatcher;
    delete collisionConfig;
}

void PedroBullet::createGround()
{
    // Crear el suelo
    btCollisionShape* groundShape = new btSphereShape(1);
    btDefaultMotionState* groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, -1, 0)));
    btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(0, groundMotionState, groundShape, btVector3(0, 0, 0));
    btRigidBody* groundRigidBody = new btRigidBody(groundRigidBodyCI);
    dynamicWorld->addRigidBody(groundRigidBody);

}

// Initialize Bullet Physics
void PedroBullet::Init() {
    collisionConfig = new btDefaultCollisionConfiguration();
    collisionDispatcher = new btCollisionDispatcher(collisionConfig);
    broadphase = new btDbvtBroadphase();
    solver = new btSequentialImpulseConstraintSolver();
    dynamicWorld = new btDiscreteDynamicsWorld(collisionDispatcher, broadphase, solver, collisionConfig);
    dynamicWorld->setGravity(btVector3(0, -9.8, 0));
}

// Update Bullet Physics
void PedroBullet::Update(float deltaTime) {
    dynamicWorld->stepSimulation(deltaTime);
}

void PedroBullet::AddRigidBody(btRigidBody* body) {

    dynamicWorld->addRigidBody(body);

    rigidbodies.push_back(body);

}
////// Add a rigid body to the simulation
//void PedroBullet::AddRigidBody(VeryReal::TransformComponent* transform, PBShapes shapeType, float mass, float friction, float restitution, PBMovementType movementType) {
//    
//    //(TransformComponent * transform, PBShapes shapeType, float mass, float friction, float restitution, PBMovementType movementType)
//    //dynamicWorld->addRigidBody(body);
//    //rigidbodies.push_back(body);
//}

void PedroBullet::RemoveRigidBody(btRigidBody* body) {

    dynamicWorld->removeRigidBody(body);

}

// Remove a rigid body from the simulation
//void PedroBullet::RemoveRigidBody(RigidBodyComponent* body) {
//
//    dynamicWorld->removeRigidBody(body->GetBulletRigidBody());
//    delete body;
//}

void PedroBullet::addForce(btRigidBody* body, btVector3 force)
{
    body->btRigidBody::applyForce(force, body->getWorldTransform().getOrigin());
}

void PedroBullet::Cleanup()
{
    //Limpieza de objetos
    //...
    //auto it = rigidbodies.begin();
    //while (it != rigidbodies.end()) {
    //    //dynamicWorld->removeRigidBody(*it);
    //    delete (*it)->getMotionState();
    //    delete (*it);
    //    it = rigidbodies.erase(it);
    //}
    //Limpieza de fisicas
    delete dynamicWorld;
    delete solver;
    delete broadphase;
    delete collisionDispatcher;
    delete collisionConfig;
}

btVector3 PedroBullet::V3ToBtV3(VeryReal::Vector3 conversion) const
{
    btVector3 newVector = btVector3(conversion.GetX(), conversion.GetY(), conversion.GetZ());
    return newVector;
}


int main() {
    // Inicializar el mundo de física
    PedroBullet::Instance()->Init();

    // Crear objetos y añadirlos al mundo de física

    // Bucle principal de la aplicación
    while (true) {
        // Actualizar el mundo de física
        PedroBullet::Instance()->Update(1.0f / 60.0f); // Ejemplo con 60Hz de frecuencia de actualización
    }


    //    //Crear una esfera   
    btCollisionShape* fallShape = new btSphereShape(1);  //asign a collition shape
    btDefaultMotionState* fallMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 50, 0)));  //asign the motion state
    btScalar mass = 1;
    btVector3 fallInertia(0, 0, 0);
    fallShape->calculateLocalInertia(mass, fallInertia);
    btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass, fallMotionState, fallShape, fallInertia);
    btRigidBody* fallRigidBody = new btRigidBody(fallRigidBodyCI);
    //dynamicWorld->addRigidBody(fallRigidBody);


    // Limpiar al finalizar
    PedroBullet::Instance()->Cleanup();

    return 0;
}
//
//int main() {
//    // Inicializar el mundo de física
//    btBroadphaseInterface* broadphase = new btDbvtBroadphase();
//    btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();
//    btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);
//    btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;
//    btDiscreteDynamicsWorld* dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);
//
//    dynamicsWorld->setGravity(btVector3(0, -10, 0));
//
//
//    // Crear el suelo
//    btCollisionShape* groundShape = new btSphereShape(1);
//    btDefaultMotionState* groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, -1, 0)));
//    btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(0, groundMotionState, groundShape, btVector3(0, 0, 0));
//    btRigidBody* groundRigidBody = new btRigidBody(groundRigidBodyCI);
//    dynamicsWorld->addRigidBody(groundRigidBody);
//
//    //Crear una esfera   
//    btCollisionShape* fallShape = new btSphereShape(1);  //asign a collition shape
//    btDefaultMotionState* fallMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 50, 0)));  //asign the motion state
//    btScalar mass = 1;
//    btVector3 fallInertia(0, 0, 0);
//    fallShape->calculateLocalInertia(mass, fallInertia);
//    btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass, fallMotionState, fallShape, fallInertia);
//    btRigidBody* fallRigidBody = new btRigidBody(fallRigidBodyCI);
//    dynamicsWorld->addRigidBody(fallRigidBody);
//
//
//    // Simulación
//
//    for (int i = 0; i < 300; i++) {
//        dynamicsWorld->stepSimulation(1 / 60.f, 10);
//
//        btTransform trans;
//        fallRigidBody->getMotionState()->getWorldTransform(trans);
//
//        std::cout << "sphere height: " << trans.getOrigin().getY() << std::endl;
//    }
//
//
//    // Limpieza
//    dynamicsWorld->removeRigidBody(fallRigidBody);
//    delete fallRigidBody->getMotionState();
//    delete fallRigidBody;
//
//    dynamicsWorld->removeRigidBody(groundRigidBody);
//    delete groundRigidBody->getMotionState();
//    delete groundRigidBody;
//
//    delete fallShape;
//    delete groundShape;
//
//    delete dynamicsWorld;
//    delete solver;
//    delete dispatcher;
//    delete collisionConfiguration;
//    delete broadphase;
//
//    return 0;
//}
