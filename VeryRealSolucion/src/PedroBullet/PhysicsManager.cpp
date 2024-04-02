#include "PhysicsManager.h"
#include "Vector3.h"
#include "PedroBullet.h"
#include <btBulletDynamicsCommon.h>

#include <btBulletCollisionCommon.h>
VeryReal::PhysicsManager::PhysicsManager()
    : collisionConfiguration(nullptr),
    dispatcher(nullptr),
    overlappingPairCache(nullptr),
    solver(nullptr),
    dynamicsWorld(nullptr) {
    // Constructor vacío
}

void VeryReal::PhysicsManager::Initialize() {
    // Inicializar el mundo de física, configuración de colisiones, etc.
    collisionConfiguration = new btDefaultCollisionConfiguration();
    dispatcher = new btCollisionDispatcher(collisionConfiguration);
    overlappingPairCache = new btDbvtBroadphase();
    solver = new btSequentialImpulseConstraintSolver();
    dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);

    dynamicsWorld->setGravity(btVector3(0, -9.81f, 0));
}

void VeryReal::PhysicsManager::Update(float deltaTime) {
    dynamicsWorld->stepSimulation(deltaTime, 10);
}

void VeryReal::PhysicsManager::Shutdown() {
    // Limpieza del mundo de física y liberación de recursos
    delete dynamicsWorld;
    delete solver;
    delete overlappingPairCache;
    delete dispatcher;
    delete collisionConfiguration;
}

btDiscreteDynamicsWorld* VeryReal::PhysicsManager::GetWorld() const {
    return dynamicsWorld;
}

void VeryReal::PhysicsManager::AddRigidBody(btRigidBody* body) {
    dynamicsWorld->addRigidBody(body);
}

void VeryReal::PhysicsManager::RemoveRigidBody(btRigidBody* body) {
    dynamicsWorld->removeRigidBody(body);
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