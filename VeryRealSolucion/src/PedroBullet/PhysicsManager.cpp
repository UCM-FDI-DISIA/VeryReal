#include "PhysicsManager.h"
#include "Vector3.h"
#include <btBulletDynamicsCommon.h>
#include <btBulletCollisionCommon.h>
#include "SceneManager.h"
#include "Scene.h"
#include "Entity.h"
#include "RigidBodyComponent.h"

#include <iostream>
#include <BulletDynamics/Dynamics/btDiscreteDynamicsWorld.h>   //gestion de colisiones, gravedad...
#include <BulletCollision/CollisionShapes/btSphereShape.h>
#include <BulletCollision/CollisionShapes/btCylinderShape.h>
#include <BulletCollision/CollisionShapes/btCapsuleShape.h>
#include <BulletCollision/CollisionDispatch/btDefaultCollisionConfiguration.h>
#include <BulletCollision/BroadphaseCollision/btDbvtBroadphase.h>
#include <BulletDynamics/ConstraintSolver/btSequentialImpulseConstraintSolver.h>
#include <LinearMath/btDefaultMotionState.h>
#include <LinearMath/btVector3.h>
#include "PhysicsValues.h"
#include "ColliderComponent.h"
#ifdef _DEBUG
#include "PhysicsDebug.h"
#include "RenderManager.h"


#endif   // _DEBUG

VeryReal::PhysicsManager::PhysicsManager()
    : collisionConfiguration(nullptr), dispatcher(nullptr), overlappingPairCache(nullptr), solver(nullptr), dynamicsWorld(nullptr) { }

//btPersistentManifold almacena los puntos de contacto entre dos objetos y proporciona métodos para acceder a ambos cuerpos.
void callBackEnter(btPersistentManifold* const& manifold) {

    const btCollisionObject* ent1 = manifold->getBody0();
    const btCollisionObject* ent2 = manifold->getBody1();

    //Si los cuerpos NO son nullptr
    if (ent1 && ent2) {
        VeryReal::RigidBodyComponent* rigidBody1 = static_cast<VeryReal::RigidBodyComponent*>(ent1->getUserPointer());
        VeryReal::RigidBodyComponent* rigidBody2 = static_cast<VeryReal::RigidBodyComponent*>(ent2->getUserPointer());

        VeryReal::ColliderComponent* colliderEntity1 = rigidBody1->GetEntity()->GetComponent<VeryReal::ColliderComponent>();
        VeryReal::ColliderComponent* colliderEntity2 = rigidBody2->GetEntity()->GetComponent<VeryReal::ColliderComponent>();
        //Si tienen colliders, colisionan
        if (colliderEntity1 && colliderEntity2) {
            colliderEntity1->OnCollisionEnter(colliderEntity2->GetEntity());
            colliderEntity2->OnCollisionEnter(colliderEntity1->GetEntity());
        }
    }
}

void callBackExit(btPersistentManifold* const& manifold) {
    const btCollisionObject* ent1 = manifold->getBody0();
    const btCollisionObject* ent2 = manifold->getBody1();

    if (ent1 && ent2) {
        VeryReal::RigidBodyComponent* rigidBody1 = static_cast<VeryReal::RigidBodyComponent*>(ent1->getUserPointer());
        VeryReal::RigidBodyComponent* rigidBody2 = static_cast<VeryReal::RigidBodyComponent*>(ent2->getUserPointer());

        VeryReal::ColliderComponent* colliderEntity1 = rigidBody1->GetEntity()->GetComponent<VeryReal::ColliderComponent>();
        VeryReal::ColliderComponent* colliderEntity2 = rigidBody2->GetEntity()->GetComponent<VeryReal::ColliderComponent>();
        if (colliderEntity1 && colliderEntity2) {

            colliderEntity1->OnCollisionExit(colliderEntity2->GetEntity());
            colliderEntity2->OnCollisionExit(colliderEntity1->GetEntity());
        }
    }
}

//Tiene que devolver un bool
//Recibe los dos objetos que están colisionando
bool onCollisionStay(btManifoldPoint& manifold, void* obj1, void* obj2) {

    const btCollisionObject* ent1 = static_cast<btCollisionObject*>(obj1);
    const btCollisionObject* ent2 = static_cast<btCollisionObject*>(obj2);

    if (ent1 && ent2) {
        VeryReal::RigidBodyComponent* rigidBody1 = static_cast<VeryReal::RigidBodyComponent*>(ent1->getUserPointer());
        VeryReal::RigidBodyComponent* rigidBody2 = static_cast<VeryReal::RigidBodyComponent*>(ent2->getUserPointer());

        VeryReal::ColliderComponent* colliderEntity1 = rigidBody1->GetEntity()->GetComponent<VeryReal::ColliderComponent>();
        VeryReal::ColliderComponent* colliderEntity2 = rigidBody2->GetEntity()->GetComponent<VeryReal::ColliderComponent>();
        if (colliderEntity1 && colliderEntity2) {
            colliderEntity1->OnCollisionStay(colliderEntity2->GetEntity());
            colliderEntity2->OnCollisionStay(colliderEntity1->GetEntity());
            return true;
        }
    }
    return false;
}

 std::pair<bool, std::string> VeryReal::PhysicsManager::InitManager() {
    collisionConfiguration = nullptr;

    dispatcher = nullptr;
    overlappingPairCache = nullptr;
    solver = nullptr;
    dynamicsWorld = nullptr;

    collisionConfiguration = new btDefaultCollisionConfiguration();
    if (!collisionConfiguration) {
        return {false, "There were mistakes creating btDefaultCollisionConfiguration"}; 
    }

    dispatcher = new btCollisionDispatcher(collisionConfiguration);
    if (!dispatcher) {
       
        return {false, "There were mistakes creating btCollisionDispatcher"};   
    }

    overlappingPairCache = new btDbvtBroadphase();
    if (!overlappingPairCache) {
        
        return {false, "There were mistakes creating btDbvtBroadphase"};  
    }

    solver = new btSequentialImpulseConstraintSolver();
    if (!solver) {
      
        return {false, "There were mistakes creating btSequentialImpulseConstraintSolver"};  
    }

    dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);
    if (!dynamicsWorld) {

        return {false, "There were mistakes creating btDiscreteDynamicsWorld"};   
    }

    gContactStartedCallback = callBackEnter;
    gContactEndedCallback = callBackExit;
    gContactProcessedCallback = onCollisionStay;

    dynamicsWorld->setGravity(btVector3(0, -9.8, 0));


#ifdef _DEBUG
    debugger = new DebugMode();
    dynamicsWorld->setDebugDrawer(debugger);
#endif             // DEBUG

    return {true, "PhysicsManager sucesfully initialized"};
 }

void VeryReal::PhysicsManager::Update(float deltaTime) {
    if (dynamicsWorld) {
        dynamicsWorld->stepSimulation(deltaTime, 10);
#ifdef _DEBUG
        if (seeObjects)
            dynamicsWorld->debugDrawWorld();
#endif   // DEBUG
    }
}

void VeryReal::PhysicsManager::Shutdown()
{
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
    if (dynamicsWorld && body) {
        dynamicsWorld->addRigidBody(body);
    }
}

void VeryReal::PhysicsManager::DeleteRigidBody(btRigidBody* body) {
    if (dynamicsWorld && body) {
        dynamicsWorld->removeRigidBody(body);
    }
}

void VeryReal::PhysicsManager::SetWorldGravity(VeryReal::Vector3 g) { dynamicsWorld->setGravity({g.GetX(), g.GetY(), g.GetZ()}); }

std::list<VeryReal::Entity*> VeryReal::PhysicsManager::MakeRayCast(VeryReal::Vector3 ray_Start, VeryReal::Vector3 ray_End) {
    auto bt_ray_start = VeryReal::PhysicsManager::Instance()->V3ToBtV3(ray_Start);
    auto bt_ray_end = VeryReal::PhysicsManager::Instance()->V3ToBtV3(ray_End);
    std::list<VeryReal::Entity*> l_ents_coll(0);

    btCollisionWorld::AllHitsRayResultCallback rayCallback(bt_ray_start, bt_ray_end);
    dynamicsWorld->rayTest(bt_ray_start, bt_ray_end, rayCallback);
    btAlignedObjectArray<const btCollisionObject*> lista_de_colisionados;
    if (rayCallback.hasHit()) {
        lista_de_colisionados = rayCallback.m_collisionObjects;
        VeryReal::Scene* scene = VeryReal::SceneManager::Instance()->GetActiveScene();
        if (scene != nullptr) {
            for (int i = 0; i < lista_de_colisionados.size(); ++i) {
                for (auto ent : scene->GetEntities()) {
                    if (ent.second->HasComponent("RigidBodyComponent")) {
                        RigidBodyComponent* comp = ent.second->GetComponent<RigidBodyComponent>();
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

VeryReal::PhysicsManager::~PhysicsManager() { Shutdown(); }

void VeryReal::PhysicsManager::addForce(btRigidBody* body, btVector3 force) {
    body->btRigidBody::applyForce(force, body->getWorldTransform().getOrigin());
}

void VeryReal::PhysicsManager::clearForces(btRigidBody* body, btVector3 force) { body->btRigidBody::clearForces(); }

btVector3 VeryReal::PhysicsManager::V3ToBtV3(VeryReal::Vector3 conversion) const {
    btVector3 newVector = btVector3(conversion.GetX(), conversion.GetY(), conversion.GetZ());
    return newVector;
}