#pragma once

#include <vector>
#include "Manager.h"
#include <list>

namespace VeryReal {
    class Vector3;
    class Entity;
    class SceneManager;
}


class btDefaultCollisionConfiguration;
class btCollisionDispatcher;
class btSequentialImpulseConstraintSolver;
class btBroadphaseInterface;
class btConstraintSolver;
class btDynamicsWorld;
class btCollisionObject;
class btDiscreteDynamicsWorld;
class btRigidBody;


///-----///
class btCollisionConfiguration;
class btBroadphaseInterface;
class btTransform;
class btVector3;
class btPersistentManifold;

enum PBShapes;
enum PBMovementType;
class RigidBodyComponent;
class ColliderComponent;




namespace VeryReal {
class VERYREAL_API PhysicsManager : public Manager<PhysicsManager> {
    friend Singleton<PhysicsManager>;
public:
    PhysicsManager();
    virtual ~PhysicsManager();

    bool Initialize();              // Inicializa el mundo de Bullet y otros componentes necesarios
    void Update(float deltaTime);   // Actualiza la simulación física
    void Shutdown();                // Limpia y libera recursos

    btDiscreteDynamicsWorld* GetWorld() const;   // Getter para el mundo físico


    // Métodos para manejar cuerpos rígidos
    //void AddRigidBody(btRigidBody* body);
    //void RemoveRigidBody(btRigidBody* body);

    void AddRigidBody(PBShapes shapeType, float mass, float friction, float restitution, PBMovementType movementType);



    std::list<VeryReal::Entity*> MakeRayCast(VeryReal::Vector3 ray_Start, VeryReal::Vector3 ray_End);

private:
    btDefaultCollisionConfiguration* collisionConfiguration;
    btCollisionDispatcher* dispatcher;
    btBroadphaseInterface* overlappingPairCache;
    btSequentialImpulseConstraintSolver* solver;
    btDiscreteDynamicsWorld* dynamicsWorld;



    ///-------//// cosas para hacer pruebas
    btDiscreteDynamicsWorld* dynamicWorld = nullptr;


    void createGround();

    void addForce(btRigidBody* body, btVector3 force);

    void clearForces(btRigidBody* body, btVector3 force);

    btVector3 V3ToBtV3(VeryReal::Vector3 conversion) const;

    // Otras variables y métodos privados si son necesarios
    };
}

/// Singleton instance
/// @return A pointer of the instance
inline VeryReal::PhysicsManager& PM() { 
    return *VeryReal::PhysicsManager::Instance(); }