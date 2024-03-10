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
#include "Collider.h"

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


//btPersistentManifold almacena los puntos de contacto entre dos objetos y proporciona métodos para acceder a ambos cuerpos.
void callBackEnter(btPersistentManifold* const& manifold) {

    const btCollisionObject* ent1 = manifold->getBody0();
    const btCollisionObject* ent2 = manifold->getBody1();

    //Si los cuerpos NO son nullptr
    if (ent1 && ent2) {

        VeryReal::Collider* colliderEntity1 = static_cast<VeryReal::Collider*>(ent1->getUserPointer());
        VeryReal::Collider* colliderEntity2 = static_cast<VeryReal::Collider*>(ent2->getUserPointer());

        //Si tienen colliders, colisionan
        if (colliderEntity1 && colliderEntity2)
        {
            colliderEntity1->onCollisionEnter(colliderEntity2->GetEntity());
            colliderEntity2->onCollisionEnter(colliderEntity1->GetEntity());
        }
    }
}

void callBackExit(btPersistentManifold* const& manifold) {

    const btCollisionObject* ent1 = manifold->getBody0();
    const btCollisionObject* ent2 = manifold->getBody1();

    if (ent1 && ent2) {

        VeryReal::Collider* colliderEntity1 = static_cast<VeryReal::Collider*>(ent1->getUserPointer());
        VeryReal::Collider* colliderEntity2 = static_cast<VeryReal::Collider*>(ent2->getUserPointer());
        if (colliderEntity1 && colliderEntity2)
        {
            colliderEntity1->onCollisionExit(colliderEntity2->GetEntity());
            colliderEntity2->onCollisionExit(colliderEntity1->GetEntity());
        }
    }
}

//Tiene que devolver un bool
//Recibe los dos objetos que están colisionando
bool callBackStay(btManifoldPoint& manifold, void* obj1, void* obj2) {

    const btCollisionObject* ent1 = static_cast<btCollisionObject*>(obj1);
    const btCollisionObject* ent2 = static_cast<btCollisionObject*>(obj2);

    if (ent1 && ent2) {

        VeryReal::Collider* colliderEntity1 = static_cast<VeryReal::Collider*>(ent1->getUserPointer());
        VeryReal::Collider* colliderEntity2 = static_cast<VeryReal::Collider*>(ent2->getUserPointer());
        if (colliderEntity1 && colliderEntity2)
        {
            colliderEntity1->onCollisionStay(colliderEntity2->GetEntity());
            colliderEntity2->onCollisionStay(colliderEntity1->GetEntity());
            return true;
        }
    }
    return false;
   
}



// Initialize Bullet Physics
void PedroBullet::Init() {
    collisionConfig = new btDefaultCollisionConfiguration();
    collisionDispatcher = new btCollisionDispatcher(collisionConfig);
    broadphase = new btDbvtBroadphase();
    solver = new btSequentialImpulseConstraintSolver();
    dynamicWorld = new btDiscreteDynamicsWorld(collisionDispatcher, broadphase, solver, collisionConfig);
    dynamicWorld->setGravity(btVector3(0, -9.8, 0));

    //Variable global a la que establecemos un callback para manejar eventos de colisiones de Bullet.
    //Cuando se produce una colisión en el mundo físico de Bullet, la función callback se activa
    gContactStartedCallback = callBackEnter;
    gContactProcessedCallback = callBackStay;
    gContactEndedCallback = callBackExit;

}

// Update Bullet Physics
void PedroBullet::Update(float deltaTime) {


    // Inicializar el mundo de física
    PedroBullet::Instance()->Init();

    // Bucle principal de la aplicación
    while (true) {

        // Actualizar el mundo de física
        dynamicWorld->stepSimulation(deltaTime);// Ejemplo con 60Hz de frecuencia de actualización

    }


    // Limpiar al finalizar
    PedroBullet::Instance()->Cleanup();

}


void PedroBullet::AddRigidBody(PBShapes shapeType, float mass, float friction, float restitution, PBMovementType movementType)
{
    VeryReal::RigidBodyComponent* body = new  VeryReal::RigidBodyComponent(shapeType, mass, friction, restitution, movementType);
    //rigidbodies.push_back(body);
}


////Remove a rigid body from the simulation
//void PedroBullet::RemoveRigidBody(VeryReal::RigidBodyComponent* body) {
//  dynamicWorld->removeRigidBody(body->GetBulletRigidBody());
//  delete body;
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
