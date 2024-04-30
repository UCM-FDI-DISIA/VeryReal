#pragma once

#include <vector>
#include "Manager.h"
#include <list>
#include "exportPedroBullet.h"

namespace VeryReal {
    class Vector3;
    class Entity;
    class SceneManager;
    class DebugMode;
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

class ColliderComponent;




namespace VeryReal {
class  PhysicsManager : public Manager<PhysicsManager> {
    friend Singleton<PhysicsManager>;
public:
   
   VERYREAL_PEDROBULLET virtual ~PhysicsManager();


VERYREAL_PEDROBULLET static bool Init() {
        PhysicsManager* a = new PhysicsManager();
    if (a != nullptr) {
        instance_pointer.reset(a);
        return true;
    }
    return false;
}
VERYREAL_PEDROBULLET bool InitManager();   // Inicializa el mundo de Bullet y otros componentes necesarios
VERYREAL_PEDROBULLET void Update(float deltaTime);   // Actualiza la simulación física
VERYREAL_PEDROBULLET void Shutdown();                // Limpia y libera recursos

    btDiscreteDynamicsWorld* GetWorld() const;   // Getter para el mundo físico

    void AddRigidBody(btRigidBody* body);


    std::list<VeryReal::Entity*> MakeRayCast(VeryReal::Vector3 ray_Start, VeryReal::Vector3 ray_End);

private:
    VERYREAL_PEDROBULLET PhysicsManager();
    btDefaultCollisionConfiguration* collisionConfiguration;
    btCollisionDispatcher* dispatcher;
    btBroadphaseInterface* overlappingPairCache;
    btSequentialImpulseConstraintSolver* solver;
    btDiscreteDynamicsWorld* dynamicsWorld;
    #ifdef _DEBUG
    DebugMode* debugger;
    #endif

    ///-------//// cosas para hacer pruebas
    //btDiscreteDynamicsWorld* dynamicWorld = nullptr;


   VERYREAL_PEDROBULLET void createGround();

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