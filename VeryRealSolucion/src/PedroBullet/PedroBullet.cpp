#include "PedroBullet.h"

#include <iostream>

#include <BulletDynamics/Dynamics/btDiscreteDynamicsWorld.h>  //gestion de colisiones, gravedad...
#include <BulletCollision/CollisionShapes/btSphereShape.h>
#include <BulletCollision/CollisionShapes/btCylinderShape.h>
#include <BulletCollision/CollisionShapes/btCapsuleShape.h>
#include <BulletDynamics/Dynamics/btDiscreteDynamicsWorld.h>
#include <BulletCollision/CollisionDispatch/btDefaultCollisionConfiguration.h>
#include <BulletCollision/BroadphaseCollision/btDbvtBroadphase.h>
#include <BulletDynamics/ConstraintSolver/btSequentialImpulseConstraintSolver.h>
#include <LinearMath/btDefaultMotionState.h>



//Método heredado de la clase Singleton por el cual iniciamos nuestro mundo físico.
void PedroBullet::Init()
{
	
	collisionConfig = new btDefaultCollisionConfiguration();
	collisionDispatcher = new btCollisionDispatcher(collisionConfig);
	this->interface = new btDbvtBroadphase();
	constraintSolver = new btSequentialImpulseConstraintSolver();
	dynamicWorld = new btDiscreteDynamicsWorld(collisionDispatcher, this->interface, constraintSolver, collisionConfig);

	dynamicWorld->setGravity(btVector3(0, -9.8, 0));



}


//Actualizamos las físicas del mundo
void PedroBullet::Update(const double& timeStep)
{
	dynamicWorld->stepSimulation(timeStep);	
}


//Añadimos un rB
void PedroBullet::addRigidbody(btRigidBody* rB)
{
	dynamicWorld->addRigidBody(rB);

}

//Eliminamos un rB
void PedroBullet::deleteRigidbody(btRigidBody* rB)
{
	rB->setUserPointer(nullptr);
	dynamicWorld->removeRigidBody(rB);
	delete rB;
}

void PedroBullet::createRigidBody(btTransform* transform)
{

}










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
//    btCollisionShape* groundShape = new btStaticPlaneShape(btVector3(0, 1, 0), 1);
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
