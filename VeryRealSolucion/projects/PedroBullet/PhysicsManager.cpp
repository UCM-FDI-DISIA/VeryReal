#include "PhysicsManager.h"

PhysicsManager::PhysicsManager()
    : collisionConfiguration(nullptr),
    dispatcher(nullptr),
    overlappingPairCache(nullptr),
    solver(nullptr),
    dynamicsWorld(nullptr) {
    // Constructor vacío
}

void PhysicsManager::Initialize() {
    // Inicializar el mundo de física, configuración de colisiones, etc.
    collisionConfiguration = new btDefaultCollisionConfiguration();
    dispatcher = new btCollisionDispatcher(collisionConfiguration);
    overlappingPairCache = new btDbvtBroadphase();
    solver = new btSequentialImpulseConstraintSolver();
    dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);

    dynamicsWorld->setGravity(btVector3(0, -9.81f, 0));
}

void PhysicsManager::Update(float deltaTime) {
    dynamicsWorld->stepSimulation(deltaTime, 10);
}

void PhysicsManager::Shutdown() {
    // Limpieza del mundo de física y liberación de recursos
    delete dynamicsWorld;
    delete solver;
    delete overlappingPairCache;
    delete dispatcher;
    delete collisionConfiguration;
}

btDiscreteDynamicsWorld* PhysicsManager::GetWorld() const {
    return dynamicsWorld;
}

void PhysicsManager::AddRigidBody(btRigidBody* body) {
    dynamicsWorld->addRigidBody(body);
}

void PhysicsManager::RemoveRigidBody(btRigidBody* body) {
    dynamicsWorld->removeRigidBody(body);
}

PhysicsManager::~PhysicsManager() {
    Shutdown();  
}