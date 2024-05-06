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
class VERYREAL_PEDROBULLET PhysicsManager : public Manager<PhysicsManager> {
    friend Singleton<PhysicsManager>;

        public:
    virtual ~PhysicsManager();

    static bool Init() {
        PhysicsManager* a = new PhysicsManager();
        if (a != nullptr) {
            instance_pointer.reset(a);
            return true;
        }
        return false;
    }
    bool InitManager();             // Inicializa el mundo de Bullet y otros componentes necesarios
    void Update(float deltaTime);   // Actualiza la simulaci�n f�sica
    void Shutdown();                // Limpia y libera recursos

    btDiscreteDynamicsWorld* GetWorld() const;   // Getter para el mundo f�sico

    void AddRigidBody(btRigidBody* body);
    void DeleteRigidBody(btRigidBody* body);
    void SetWorldGravity(VeryReal::Vector3 g);
    
    std::list<VeryReal::Entity*> MakeRayCast(VeryReal::Vector3 ray_Start, VeryReal::Vector3 ray_End);
    #ifdef _DEBUG
        inline void SeeDebugColliders(bool newValue) { seeObjects = newValue; }
    #endif

        private:
    PhysicsManager();
    btDefaultCollisionConfiguration* collisionConfiguration = nullptr;
    btCollisionDispatcher* dispatcher = nullptr;
    btBroadphaseInterface* overlappingPairCache = nullptr;
    btSequentialImpulseConstraintSolver* solver = nullptr;
    btDiscreteDynamicsWorld* dynamicsWorld = nullptr;
#ifdef _DEBUG
    DebugMode* debugger = nullptr;
    bool seeObjects = true;

#endif

    ///-------//// cosas para hacer pruebas
    //btDiscreteDynamicsWorld* dynamicWorld = nullptr;

    void createGround();

    void addForce(btRigidBody* body, btVector3 force);

    void clearForces(btRigidBody* body, btVector3 force);

    btVector3 V3ToBtV3(VeryReal::Vector3 conversion) const;

    // Otras variables y m�todos privados si son necesarios
};
}

/// Singleton instance
/// @return A pointer of the instance
inline VeryReal::PhysicsManager& PM() { return *VeryReal::PhysicsManager::Instance(); }