#include "PhysicsManager.h"
#include "Vector3.h"
#include "PedroBullet.h"
#include <btBulletDynamicsCommon.h>
#include <btBulletCollisionCommon.h>

VeryReal::PhysicsManager::PhysicsManager()
    : collisionConfiguration(nullptr), dispatcher(nullptr), overlappingPairCache(nullptr), solver(nullptr), dynamicsWorld(nullptr) {
    // Constructor vac�o
}

bool VeryReal::PhysicsManager::Initialize() {
    // Inicializar el mundo de f�sica, configuraci�n de colisiones, etc.
    collisionConfiguration = new btDefaultCollisionConfiguration();
    if (!collisionConfiguration) {
        return false;   // Fall� la creaci�n de collisionConfiguration
    }

    dispatcher = new btCollisionDispatcher(collisionConfiguration);
    if (!dispatcher) {
        Shutdown();  
        return false;   // Fall� la creaci�n de dispatcher
    }

    overlappingPairCache = new btDbvtBroadphase();
    if (!overlappingPairCache) {
        Shutdown();  
        return false;   // Fall� la creaci�n de overlappingPairCache
    }

    solver = new btSequentialImpulseConstraintSolver();
    if (!solver) {
        Shutdown();  
        return false;   // Fall� la creaci�n de solver
    }

    dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);
    if (!dynamicsWorld) {
        Shutdown();  
        return false;   // Fall� la creaci�n de dynamicsWorld
    }

    dynamicsWorld->setGravity(btVector3(0, -9.81f, 0));
    return true;   // Inicializaci�n exitosa
}

void VeryReal::PhysicsManager::Update(float deltaTime) {
    if (dynamicsWorld) {
        dynamicsWorld->stepSimulation(deltaTime, 10);
    }
}

void VeryReal::PhysicsManager::Shutdown() {
    // Limpieza del mundo de f�sica y liberaci�n de recursos
    if (dynamicsWorld) {
        delete dynamicsWorld;
    }
    if (solver) {
        delete solver;
    }
    if (overlappingPairCache) {
        delete overlappingPairCache;
    }
    if (dispatcher) {
        delete dispatcher;
    }
    if (collisionConfiguration) {
        delete collisionConfiguration;
    }
}

btDiscreteDynamicsWorld* VeryReal::PhysicsManager::GetWorld() const { return dynamicsWorld; }

void VeryReal::PhysicsManager::AddRigidBody(btRigidBody* body) {
    if (dynamicsWorld) {
        dynamicsWorld->addRigidBody(body);
    }
}

void VeryReal::PhysicsManager::RemoveRigidBody(btRigidBody* body) {
    if (dynamicsWorld) {
        dynamicsWorld->removeRigidBody(body);
    }
}

//btAlignedObjectArray<const btCollisionObject*> VeryReal::PhysicsManager::MakeRayCast(VeryReal::Vector3 ray_Start, VeryReal::Vector3 ray_End) {
//    auto bt_ray_start = PedroBullet::Instance()->V3ToBtV3(ray_Start);
//    auto bt_ray_end = PedroBullet::Instance()->V3ToBtV3(ray_End);
//
//    btCollisionWorld::AllHitsRayResultCallback rayCallback(bt_ray_start, bt_ray_end);
//    dynamicsWorld->rayTest(bt_ray_start, bt_ray_end, rayCallback);
//    btAlignedObjectArray<const btCollisionObject*> lista_de_colisionados;
//    if (rayCallback.hasHit()) {
//        lista_de_colisionados = rayCallback.m_collisionObjects;
//    }
//    return lista_de_colisionados;
//}

VeryReal::PhysicsManager::~PhysicsManager() {
    Shutdown();  
}