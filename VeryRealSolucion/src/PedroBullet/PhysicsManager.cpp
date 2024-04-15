#include "PhysicsManager.h"
#include "Vector3.h"
#include <btBulletDynamicsCommon.h>
#include <btBulletCollisionCommon.h>
#include "SceneManager.h"
#include "Scene.h"
#include "Entity.h"
#include "RigidBodyComponent.h"

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
#include "PhysicsValues.h"
#include "ColliderComponent.h"

VeryReal::PhysicsManager::PhysicsManager(): collisionConfiguration(nullptr), dispatcher(nullptr), overlappingPairCache(nullptr), solver(nullptr), dynamicsWorld(nullptr) { }

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

void VeryReal::PhysicsManager::AddRigidBody(PBShapes shapeType, float mass, float friction, float restitution, PBMovementType movementType) {
    VeryReal::RigidBodyComponent* body = new VeryReal::RigidBodyComponent();
    body->InitComponent(shapeType, mass, friction, restitution, movementType);
    
    //rigidbodies.push_back(body);
}

std::list<VeryReal::Entity*> VeryReal::PhysicsManager::MakeRayCast(VeryReal::Vector3 ray_Start, VeryReal::Vector3 ray_End) {
    auto bt_ray_start = VeryReal::PhysicsManager::Instance()->V3ToBtV3(ray_Start);
    auto bt_ray_end = VeryReal::PhysicsManager::Instance()->V3ToBtV3(ray_End);
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
                    RigidBodyComponent* comp = ent.second->GetComponent<RigidBodyComponent>();
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



///-------//// cosas para hacer pruebas


void VeryReal::PhysicsManager::createGround() {
    // Crear el suelo
    btCollisionShape* groundShape = new btSphereShape(1);
    btDefaultMotionState* groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, -1, 0)));
    btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(0, groundMotionState, groundShape, btVector3(0, 0, 0));
    btRigidBody* groundRigidBody = new btRigidBody(groundRigidBodyCI);
    dynamicWorld->addRigidBody(groundRigidBody);
}



void VeryReal::PhysicsManager::addForce(btRigidBody* body, btVector3 force) {
    body->btRigidBody::applyForce(force, body->getWorldTransform().getOrigin()); 
}

void VeryReal::PhysicsManager::clearForces(btRigidBody* body, btVector3 force) {
    body->btRigidBody::clearForces();
}

btVector3 VeryReal::PhysicsManager::V3ToBtV3(VeryReal::Vector3 conversion) const {
    btVector3 newVector = btVector3(conversion.GetX(), conversion.GetY(), conversion.GetZ());
    return newVector;
}

//btPersistentManifold almacena los puntos de contacto entre dos objetos y proporciona métodos para acceder a ambos cuerpos.
void callBackEnter(btPersistentManifold* const& manifold) {

    const btCollisionObject* ent1 = manifold->getBody0();
    const btCollisionObject* ent2 = manifold->getBody1();

    //Si los cuerpos NO son nullptr
    if (ent1 && ent2) {

        VeryReal::ColliderComponent* colliderEntity1 = static_cast<VeryReal::ColliderComponent*>(ent1->getUserPointer());
        VeryReal::ColliderComponent* colliderEntity2 = static_cast<VeryReal::ColliderComponent*>(ent2->getUserPointer());

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

        VeryReal::ColliderComponent* colliderEntity1 = static_cast<VeryReal::ColliderComponent*>(ent1->getUserPointer());
        VeryReal::ColliderComponent* colliderEntity2 = static_cast<VeryReal::ColliderComponent*>(ent2->getUserPointer());
        if (colliderEntity1 && colliderEntity2) {
            colliderEntity1->OnCollisionExit(colliderEntity2->GetEntity());
            colliderEntity2->OnCollisionExit(colliderEntity1->GetEntity());
        }
    }
}

//Tiene que devolver un bool
//Recibe los dos objetos que están colisionando
bool callBackStay(btManifoldPoint& manifold, void* obj1, void* obj2) {

    const btCollisionObject* ent1 = static_cast<btCollisionObject*>(obj1);
    const btCollisionObject* ent2 = static_cast<btCollisionObject*>(obj2);

    if (ent1 && ent2) {

        VeryReal::ColliderComponent* colliderEntity1 = static_cast<VeryReal::ColliderComponent*>(ent1->getUserPointer());
        VeryReal::ColliderComponent* colliderEntity2 = static_cast<VeryReal::ColliderComponent*>(ent2->getUserPointer());
        if (colliderEntity1 && colliderEntity2) {
            colliderEntity1->OnCollisionStay(colliderEntity2->GetEntity());
            colliderEntity2->OnCollisionStay(colliderEntity1->GetEntity());
            return true;
        }
    }
    return false;
}