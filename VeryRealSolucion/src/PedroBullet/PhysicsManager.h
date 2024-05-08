#pragma once

#include <vector>
#include "Manager.h"
#include <list>
#include "exportPedroBullet.h"
#include <string>
#include <vector>
#include <queue>
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
class btCollisionConfiguration;
class btTransform;
class btVector3;
class btPersistentManifold;

enum PBShapes;
enum PBMovementType;

class ColliderComponent;
class TransformComponent;

namespace VeryReal {
    struct RaycastColision {
    Entity* ent;
        float dist;

};
    struct CompareMyStruct {
        bool operator()(const RaycastColision& a, const RaycastColision& b) const {
            return a.dist > b.dist;   // Orden ascendente basado en la distancia
        }
    };

class VERYREAL_PEDROBULLET PhysicsManager : public Manager<PhysicsManager> {
    friend Singleton<PhysicsManager>;

  public:
    virtual ~PhysicsManager();

    static std::pair<bool, std::string> Init() {
        PhysicsManager* a = new PhysicsManager();
        if (a != nullptr) {
            instance_pointer.reset(a);
            std::pair<bool, std::string> r = a->InitManager();   //inicializamos el manager
            if (!r.first) {
                delete a;   //el init manager da error pero se tiene que destruir memoria
                return {false, "PhysicsManager pointer had a problem while it was initializing"};
            }
            return {true, "PhysicsManager pointer sucesfully initialized"};
        }
        return {false, "PhysicsManager pointer had a problem while it was initializing"};
    }
    std::pair<bool, std::string> InitManager();   // Inicializa el mundo de Bullet y otros componentes necesarios
    void Update(float deltaTime);   // Actualiza la simulación física
    void Shutdown();                // Limpia y libera recursos

    btDiscreteDynamicsWorld* GetWorld() const;   // Getter para el mundo físico

    void AddRigidBody(btRigidBody* body);
    void DeleteRigidBody(btRigidBody* body);
    void SetWorldGravity(VeryReal::Vector3 g);
    
   std::priority_queue<RaycastColision, std::vector<RaycastColision>, CompareMyStruct> MakeRayCast(VeryReal::Vector3 ray_Start,
                                                                                                    VeryReal::Vector3 ray_End);
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
    void addForce(btRigidBody* body, btVector3 force);

    void clearForces(btRigidBody* body, btVector3 force);

    btVector3 V3ToBtV3(VeryReal::Vector3 conversion) const;

};
}

/// Singleton instance
/// @return A pointer of the instance
inline VeryReal::PhysicsManager& PM() { return *VeryReal::PhysicsManager::Instance(); }