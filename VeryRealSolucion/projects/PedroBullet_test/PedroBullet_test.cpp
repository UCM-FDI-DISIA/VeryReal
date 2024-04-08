// PedroBullet_test.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>

#include "PhysicsManager.h"
#include "Vector3.h"


//int main()
//{
//	PB().Init();
// 
//  VeryReal::PhysicsManager::Instance()->InitManager("app");
//	uint32_t startTime, frameTime;
//	startTime = 0;
//	while (true) {
//		frameTime = 3;
//		
//		if (frameTime >= 3) {
//			// Fisicas
//			// Update (Componentes)
//			// Render
//			// Sonido
//			
//		}
//		PB().Update(3);
//	}
//	return 0;
//}

// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln



int main() {
    //// Inicializar el mundo de física
    //PedroBullet::Instance()->Init();

    //// Crear objetos y añadirlos al mundo de física

    //// Bucle principal de la aplicación
    //while (true) {
    //    // Actualizar el mundo de física
    //    PedroBullet::Instance()->Update(1.0f / 60.0f); // Ejemplo con 60Hz de frecuencia de actualización
    //}

    //// Limpiar al finalizar
    //PedroBullet::Instance()->Cleanup();
    //std::cout << "Hola buenas tardes\n";
    //VeryReal::PhysicsManager::Instance()->MakeRayCast(VeryReal::Vector3(0, 0, 0), VeryReal::Vector3(100, 0, 0));
    
    
    return 0;
}


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
