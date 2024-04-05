#include "PhysicsManager.h"
#include "Vector3.h"
#include "PedroBullet.h"
#include <btBulletDynamicsCommon.h>
#include <btBulletCollisionCommon.h>
#include "SceneManager.h"

VeryReal::PhysicsManager::PhysicsManager()
    : collisionConfiguration(nullptr), dispatcher(nullptr), overlappingPairCache(nullptr), solver(nullptr), dynamicsWorld(nullptr) {
    // Constructor vacío
}

bool VeryReal::PhysicsManager::Initialize() {
    // Inicializar el mundo de física, configuración de colisiones, etc.
    collisionConfiguration = new btDefaultCollisionConfiguration();
    if (!collisionConfiguration) {
        return false;   // Falló la creación de collisionConfiguration
    }

    dispatcher = new btCollisionDispatcher(collisionConfiguration);
    if (!dispatcher) {
        Shutdown();  
        return false;   // Falló la creación de dispatcher
    }

    overlappingPairCache = new btDbvtBroadphase();
    if (!overlappingPairCache) {
        Shutdown();  
        return false;   // Falló la creación de overlappingPairCache
    }

    solver = new btSequentialImpulseConstraintSolver();
    if (!solver) {
        Shutdown();  
        return false;   // Falló la creación de solver
    }

    dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);
    if (!dynamicsWorld) {
        Shutdown();  
        return false;   // Falló la creación de dynamicsWorld
    }

    dynamicsWorld->setGravity(btVector3(0, -9.81f, 0));
    return true;   // Inicialización exitosa
}

void VeryReal::PhysicsManager::Update(float deltaTime) {
    if (dynamicsWorld) {
        dynamicsWorld->stepSimulation(deltaTime, 10);
    }
}

void VeryReal::PhysicsManager::Shutdown() {
    // Limpieza del mundo de física y liberación de recursos
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

std::list<VeryReal::Entity*> VeryReal::PhysicsManager::MakeRayCast(VeryReal::Vector3 ray_Start, VeryReal::Vector3 ray_End) {
    auto bt_ray_start = PedroBullet::Instance()->V3ToBtV3(ray_Start);
    auto bt_ray_end = PedroBullet::Instance()->V3ToBtV3(ray_End);
    std::list<VeryReal::Entity*> l_ents_coll(0);

    btCollisionWorld::AllHitsRayResultCallback rayCallback(bt_ray_start, bt_ray_end);
    dynamicsWorld->rayTest(bt_ray_start, bt_ray_end, rayCallback);
    btAlignedObjectArray<const btCollisionObject*> lista_de_colisionados;
    if (rayCallback.hasHit()) {
        lista_de_colisionados = rayCallback.m_collisionObjects;
        for (int i = 0; i < lista_de_colisionados.size(); ++i) {
            /*VeryReal::Scene* scene = VeryReal::SceneManager::GetScene("Play");
            if (scene != nullptr) {
                for ()
                    lista_de_colisionados [i]->getCollisionShape()
            }*/
        }
    }
    return l_ents_coll;
}

VeryReal::PhysicsManager::~PhysicsManager() {
    Shutdown();  
}