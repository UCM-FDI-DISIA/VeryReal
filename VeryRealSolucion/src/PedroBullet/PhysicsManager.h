#pragma once

#include <btBulletDynamicsCommon.h>
#include <vector>

class PhysicsManager {
public:
    PhysicsManager();
    ~PhysicsManager();

    void Initialize();  // Inicializa el mundo de Bullet y otros componentes necesarios
    void Update(float deltaTime);  // Actualiza la simulaci�n f�sica
    void Shutdown();  // Limpia y libera recursos

    btDiscreteDynamicsWorld* GetWorld() const;  // Getter para el mundo f�sico

    // M�todos para manejar cuerpos r�gidos
    void AddRigidBody(btRigidBody* body);
    void RemoveRigidBody(btRigidBody* body);

private:
    btDefaultCollisionConfiguration* collisionConfiguration;
    btCollisionDispatcher* dispatcher;
    btBroadphaseInterface* overlappingPairCache;
    btSequentialImpulseConstraintSolver* solver;
    btDiscreteDynamicsWorld* dynamicsWorld;

    // Otras variables y m�todos privados si son necesarios
};