#pragma once

#include <btBulletDynamicsCommon.h>
#include <vector>
#include "Manager.h"

namespace VeryReal {
    class Vector3;
}

namespace VeryReal {
    class PhysicsManager : public Manager<PhysicsManager> {
    public:
        PhysicsManager();
        ~PhysicsManager();

        void Initialize();              // Inicializa el mundo de Bullet y otros componentes necesarios
        void Update(float deltaTime);   // Actualiza la simulación física
        void Shutdown();                // Limpia y libera recursos

        btDiscreteDynamicsWorld* GetWorld() const;   // Getter para el mundo físico

        // Métodos para manejar cuerpos rígidos
        void AddRigidBody(btRigidBody* body);
        void RemoveRigidBody(btRigidBody* body);

        btAlignedObjectArray<const btCollisionObject*> MakeRayCast(VeryReal::Vector3 ray_Start, VeryReal::Vector3 ray_End);

    private:
        btDefaultCollisionConfiguration* collisionConfiguration;
        btCollisionDispatcher* dispatcher;
        btBroadphaseInterface* overlappingPairCache;
        btSequentialImpulseConstraintSolver* solver;
        btDiscreteDynamicsWorld* dynamicsWorld;

        // Otras variables y métodos privados si son necesarios
    };
}