#include "PhysicsManager.h"
#include "Vector3.h"
#include <btBulletDynamicsCommon.h>
#include <btBulletCollisionCommon.h>
#include "SceneManager.h"
#include "PedroBullet.h"
#include "Scene.h"
#include "Entity.h"
#include "RigidBodyComponent.h"


bool VeryReal::PhysicsManager::Initialize() {
    collisionConfiguration=nullptr;

    dispatcher = nullptr;
    overlappingPairCache = nullptr;
    solver=nullptr; 
    dynamicsWorld = nullptr;
        // Constructor vac�o
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

std::list<VeryReal::Entity*> VeryReal::PhysicsManager::MakeRayCast(VeryReal::Vector3 ray_Start, VeryReal::Vector3 ray_End) {
    auto bt_ray_start = PedroBullet::Instance()->V3ToBtV3(ray_Start);
    auto bt_ray_end = PedroBullet::Instance()->V3ToBtV3(ray_End);
    std::list<VeryReal::Entity*> l_ents_coll(0);

    btCollisionWorld::AllHitsRayResultCallback rayCallback(bt_ray_start, bt_ray_end);
    dynamicsWorld->rayTest(bt_ray_start, bt_ray_end, rayCallback);
    btAlignedObjectArray<const btCollisionObject*> lista_de_colisionados;
    if (rayCallback.hasHit()) {
        lista_de_colisionados = rayCallback.m_collisionObjects;
        VeryReal::Scene* scene = VeryReal::SceneManager::Instance()->GetScene("Play");
        if (scene != nullptr) {
            for (auto ent : scene->GetEntities()) {
                if (ent.second->HasComponent("RigidBodyComponent")) {
                    RigidBodyComponent* comp = ent.second->GetComponent<RigidBodyComponent>("RigidBodyComponent");
                    for (int i = 0; i < lista_de_colisionados.size(); ++i) {
                        if (lista_de_colisionados [i]->getCollisionShape() == comp->GetCollisionShape()) {
                            l_ents_coll.push_back(ent.second);
                        }
                    }
                }
                
            }
        }
        
    }
    return l_ents_coll;
}

VeryReal::PhysicsManager::~PhysicsManager() {
    Shutdown();  
}