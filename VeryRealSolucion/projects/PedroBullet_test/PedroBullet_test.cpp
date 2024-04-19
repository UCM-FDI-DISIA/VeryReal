#include <iostream>
#include "PhysicsManager.h"
#include "RigidBodyComponent.h"
#include "Vector3.h"
#include "Creator.h"
#include "CreatorRigidBodyComponent.h"
#include "SceneManager.h"
#include "CreatorColliderComponent.h"

#include <ErrorInformant.h>
#include "TransformComponent.h"
#include "CreatorTransformComponent.h"
#include "Scene.h"
#include "Entity.h"

using namespace VeryReal;

//int main() {
//
//    bool t = VeryReal::Creator::Init();
//    VeryReal::SceneManager::Init();
//    VeryReal::PhysicsManager::Init();
//    if (t) {
//        std::cout << "true";
//    }
//    else {
//
//        std::cout << "false";
//    }
//
//
//    PhysicsManager::Instance()->InitManager();
//
//
//    Creator::Instance()->AddCreator("RigidBodyComponent", new CreatorRigidBodyComponent());
//    Creator::Instance()->AddCreator("ColliderComponent", new CreatorColliderComponent());
//
//
//    //estas lineas son las que dan leacks en las fisicas pero hay que esperar a arreglos de arquitectura
//    Creator::Instance()->GetCreator("RigidBodyComponent")->AddParameter("shapeType", 1);
//    Creator::Instance()->GetCreator("RigidBodyComponent")->AddParameter("mass", float(1));
//    Creator::Instance()->GetCreator("RigidBodyComponent")->AddParameter("friction", float(0));
//    Creator::Instance()->GetCreator("RigidBodyComponent")->AddParameter("restitution", float(0));
//    Creator::Instance()->GetCreator("RigidBodyComponent")->AddParameter("movementType", int(0));
//    Creator::Instance()->GetCreator("RigidBodyComponent")->AddParameter("trigger", true);
//    //------------------------------------------------------------------------------------------------//
//    /*Scene* s = SceneManager::Instance()->AddScene("Play", true);
//    s = SceneManager::Instance()->GetScene("Play");
//
//    Entity* e = s->AddEntity("Player");
//
//    Component* transform = e->AddComponent("RigidBodyComponent");
//
//    Component* node_collider = e->AddComponent("ColliderComponent");
//
//    std::cout << SceneManager::Instance()->GetScene("Play")->GetEntity("Player")->HasComponent("RigidBodyComponent") << "\n";
//    std::cout << SceneManager::Instance()->GetScene("Play")->GetEntity("Player")->HasComponent("ColliderComponent") << "\n";
//

#include <iostream>
#include "PhysicsManager.h"
#include "Vector3.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Entity.h"
#include "RigidBodyComponent.h"
#include "TransformComponent.h"

using namespace VeryReal;

int main() {
    // Inicialización de los sistemas necesarios
    if (!Creator::Init() || !SceneManager::Init() || !PhysicsManager::Init()) {
        std::cerr << "Initialization failed." << std::endl;
        return -1;
    }

    PhysicsManager::Instance()->InitManager();

    // Configuración de la escena
    Scene* scene = SceneManager::Instance()->AddScene("Play", true);
    Entity* entity1 = scene->AddEntity("Entity1");
    Entity* entity2 = scene->AddEntity("Entity2");

        Creator::Instance()->AddCreator("RigidBodyComponent", new CreatorRigidBodyComponent());
        Creator::Instance()->AddCreator("ColliderComponent", new CreatorColliderComponent());
        Creator::Instance()->AddCreator("TransformComponent", new CreatorTransformComponent());

        //estas lineas son las que dan leacks en las fisicas pero hay que esperar a arreglos de arquitectura
        Creator::Instance()->GetCreator("RigidBodyComponent")->AddParameter("shapeType", 1);
        Creator::Instance()->GetCreator("RigidBodyComponent")->AddParameter("mass", float(1));
        Creator::Instance()->GetCreator("RigidBodyComponent")->AddParameter("friction", float(0));
        Creator::Instance()->GetCreator("RigidBodyComponent")->AddParameter("restitution", float(0));
        Creator::Instance()->GetCreator("RigidBodyComponent")->AddParameter("movementType", int(0));
        Creator::Instance()->GetCreator("RigidBodyComponent")->AddParameter("trigger", true);
        //------------------------------------------------------------------------------------------------//

        Component* rigidBody1 = entity1->AddComponent("RigidBodyComponent");
        Component* node_collider1 = entity1->AddComponent("ColliderComponent");
        Component* transform1 = entity1->AddComponent("TransformComponent");
        

        Component* rigidBody2 = entity2->AddComponent("RigidBodyComponent");
        Component* node_collider2 = entity2->AddComponent("ColliderComponent");
        Component* transform2 = entity2->AddComponent("TransformComponent");


        VeryReal::TransformComponent* entity1_transform =
            VeryReal::SceneManager::Instance()->GetScene("Play")->GetEntity("Entity1")->GetComponent<VeryReal::TransformComponent>();
        entity1_transform->SetPosition(Vector3(0, 0, 10)); 

        VeryReal::RigidBodyComponent* entity1_rigidBody =
            VeryReal::SceneManager::Instance()->GetScene("Play")->GetEntity("Entity1")->GetComponent<VeryReal::RigidBodyComponent>();
        entity1_rigidBody->InitComponent(SHAPES_BOX, 1.0f, 0.5f, 0.5f, MOVEMENT_TYPE_STATIC, false, Vector3(1, 1, 1));


                    VeryReal::TransformComponent* entity2_transform =
        VeryReal::SceneManager::Instance()->GetScene("Play")->GetEntity("Entity2")->GetComponent<VeryReal::TransformComponent>();
    entity2_transform->SetPosition(Vector3(0, 0, 20)); 

            VeryReal::RigidBodyComponent* entity2_rigidBody =
        VeryReal::SceneManager::Instance()->GetScene("Play")->GetEntity("Entity2")->GetComponent<VeryReal::RigidBodyComponent>();
    entity2_rigidBody->InitComponent(SHAPES_BOX, 1.0f, 0.5f, 0.5f, MOVEMENT_TYPE_STATIC, false, Vector3(1, 1, 1));



    // Añadir los cuerpos rígidos al mundo físico
    //PhysicsManager::Instance()->AddRigidBody(entity1_rigidBody->GetBulletRigidBody());
    //PhysicsManager::Instance()->AddRigidBody(entity2_rigidBody->GetBulletRigidBody());

    // Realizar un raycast desde el origen hacia z positivo
    Vector3 rayStart(0, 0, 0);
    Vector3 rayEnd(0, 0, 30);
    auto hitEntities = PhysicsManager::Instance()->MakeRayCast(rayStart, rayEnd);

    // Mostrar resultados del raycast
    std::cout << "Raycast hit " << hitEntities.size() << " entities." << std::endl;
    for (auto& entity : hitEntities) {
        std::cout << "Hit entity: " << entity->HasComponent("RigidBodyComponent") << std::endl;
    }



    return 0;
}
