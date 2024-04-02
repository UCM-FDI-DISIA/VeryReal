#include "BasicPhysicsWorld.h"

BasicPhysicsWorld::BasicPhysicsWorld()
    : dynamicsWorld(nullptr), groundBody(nullptr), fallingBody(nullptr) {
}

bool BasicPhysicsWorld::InitializeWorld() {
    btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();
    btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);
    btBroadphaseInterface* overlappingPairCache = new btDbvtBroadphase();
    btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver();

    dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);
    if (!dynamicsWorld) {
        // Limpieza y retorno falso si la creación falló
        delete solver;
        delete overlappingPairCache;
        delete dispatcher;
        delete collisionConfiguration;
        return false;
    }

    dynamicsWorld->setGravity(btVector3(0, -10, 0));

    groundBody = CreateGround();
    if (!groundBody) {
        // Limpieza y retorno falso si la creación falló
        Cleanup(); 
        return false;
    }

    fallingBody = CreateFallingObject();
    if (!fallingBody) {
        // Limpieza y retorno falso si la creación falló
        Cleanup(); 
        return false;
    }

    return true;   // Todo se creó correctamente
}

btRigidBody* BasicPhysicsWorld::CreateGround() {
    btCollisionShape* groundShape = new btStaticPlaneShape(btVector3(0, 1, 0), 1);
    btDefaultMotionState* groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, -1, 0)));
    btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(0, groundMotionState, groundShape, btVector3(0, 0, 0));
    btRigidBody* groundBody = new btRigidBody(groundRigidBodyCI);
    dynamicsWorld->addRigidBody(groundBody);
    return groundBody;
}

btRigidBody* BasicPhysicsWorld::CreateFallingObject() {
    btCollisionShape* fallShape = new btSphereShape(1);
    btDefaultMotionState* fallMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 50, 0)));
    btScalar mass = 1;
    btVector3 fallInertia(0, 0, 0);
    fallShape->calculateLocalInertia(mass, fallInertia);
    btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass, fallMotionState, fallShape, fallInertia);
    btRigidBody* fallBody = new btRigidBody(fallRigidBodyCI);
    dynamicsWorld->addRigidBody(fallBody);
    return fallBody;
}

void BasicPhysicsWorld::Update(float deltaTime) {
    dynamicsWorld->stepSimulation(deltaTime);
}

void BasicPhysicsWorld::Cleanup() {
    // Limpieza de cuerpos rígidos y formas de colisión
    dynamicsWorld->removeRigidBody(fallingBody);
    delete fallingBody->getMotionState();
    delete fallingBody;

    dynamicsWorld->removeRigidBody(groundBody);
    delete groundBody->getMotionState();
    delete groundBody;

}

BasicPhysicsWorld::~BasicPhysicsWorld() {
    delete dynamicsWorld;  
}
