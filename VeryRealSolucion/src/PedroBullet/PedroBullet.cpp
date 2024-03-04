#include "PedroBullet.h"



// Constructor
PedroBullet::PedroBullet() :
    dynamicWorld(nullptr),
    collisionConfig(nullptr),
    collisionDispatcher(nullptr),
    broadphase(nullptr),
    solver(nullptr) {
}

// Destructor
PedroBullet::~PedroBullet() {
    delete dynamicWorld;
    delete solver;
    delete broadphase;
    delete collisionDispatcher;
    delete collisionConfig;
}

// Initialize Bullet Physics
void PedroBullet::Init() {
    collisionConfig = new btDefaultCollisionConfiguration();
    collisionDispatcher = new btCollisionDispatcher(collisionConfig);
    broadphase = new btDbvtBroadphase();
    solver = new btSequentialImpulseConstraintSolver();
    dynamicWorld = new btDiscreteDynamicsWorld(collisionDispatcher, broadphase, solver, collisionConfig);
    dynamicWorld->setGravity(btVector3(0, -9.8, 0));
}

// Update Bullet Physics
void PedroBullet::Update(float deltaTime) {
    dynamicWorld->stepSimulation(deltaTime);
}

// Add a rigid body to the simulation
void PedroBullet::AddRigidBody(btRigidBody* body) {
    dynamicWorld->addRigidBody(body);
}

// Remove a rigid body from the simulation
void PedroBullet::RemoveRigidBody(btRigidBody* body) {
    dynamicWorld->removeRigidBody(body);
}

void PedroBullet::createRigidBody(btTransform* transform)
{

}








//
//
//int main() {
//    // Inicializar el mundo de física
//    PedroBullet::Instance()->Init();
//
//    // Crear objetos y añadirlos al mundo de física
//
//    // Bucle principal de la aplicación
//    while (true) {
//        // Actualizar el mundo de física
//        PedroBullet::Instance()->Update(1.0f / 60.0f); // Ejemplo con 60Hz de frecuencia de actualización
//    }
//
//    // Limpiar al finalizar
//    PedroBullet::Instance()->Cleanup();
//
//    return 0;
//}
//
//


//
//
//
//
//int main() {
//    // Inicializar el mundo de física
//    btBroadphaseInterface* broadphase = new btDbvtBroadphase();
//    btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();
//    btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);
//    btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;
//    btDiscreteDynamicsWorld* dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);
//
//    dynamicsWorld->setGravity(btVector3(0, -10, 0));
//
//    // Crear el suelo
//    btCollisionShape* groundShape = new btSphereShape(1);
//    btDefaultMotionState* groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, -1, 0)));
//    btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(0, groundMotionState, groundShape, btVector3(0, 0, 0));
//    btRigidBody* groundRigidBody = new btRigidBody(groundRigidBodyCI);
//    dynamicsWorld->addRigidBody(groundRigidBody);
//
//    // Crear una esfera
//    btCollisionShape* fallShape = new btSphereShape(1);
//    btDefaultMotionState* fallMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 50, 0)));
//    btScalar mass = 1;
//    btVector3 fallInertia(0, 0, 0);
//    fallShape->calculateLocalInertia(mass, fallInertia);
//    btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass, fallMotionState, fallShape, fallInertia);
//    btRigidBody* fallRigidBody = new btRigidBody(fallRigidBodyCI);
//    dynamicsWorld->addRigidBody(fallRigidBody);
//
//    // Simulación
//    for (int i = 0; i < 300; i++) {
//        dynamicsWorld->stepSimulation(1 / 60.f, 10);
//
//        btTransform trans;
//        fallRigidBody->getMotionState()->getWorldTransform(trans);
//
//        std::cout << "sphere height: " << trans.getOrigin().getY() << std::endl;
//    }
//
//    // Limpieza
//    dynamicsWorld->removeRigidBody(fallRigidBody);
//    delete fallRigidBody->getMotionState();
//    delete fallRigidBody;
//
//    dynamicsWorld->removeRigidBody(groundRigidBody);
//    delete groundRigidBody->getMotionState();
//    delete groundRigidBody;
//
//    delete fallShape;
//    delete groundShape;
//
//    delete dynamicsWorld;
//    delete solver;
//    delete dispatcher;
//    delete collisionConfiguration;
//    delete broadphase;
//
//    return 0;
//}
