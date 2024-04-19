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

int main() {

    bool t = VeryReal::Creator::Init();
    VeryReal::SceneManager::Init();
    VeryReal::PhysicsManager::Init();
    if (t) {
        std::cout << "true";
    }
    else {

        std::cout << "false";
    }


    PhysicsManager::Instance()->InitManager();


    Creator::Instance()->AddCreator("RigidBodyComponent", new CreatorRigidBodyComponent());
    Creator::Instance()->AddCreator("ColliderComponent", new CreatorColliderComponent());


    //estas lineas son las que dan leacks en las fisicas pero hay que esperar a arreglos de arquitectura
    Creator::Instance()->GetCreator("RigidBodyComponent")->AddParameter("shapeType", 1);
    Creator::Instance()->GetCreator("RigidBodyComponent")->AddParameter("mass", float(1));
    Creator::Instance()->GetCreator("RigidBodyComponent")->AddParameter("friction", float(0));
    Creator::Instance()->GetCreator("RigidBodyComponent")->AddParameter("restitution", float(0));
    Creator::Instance()->GetCreator("RigidBodyComponent")->AddParameter("movementType", int(0));
    Creator::Instance()->GetCreator("RigidBodyComponent")->AddParameter("trigger", true);
    //------------------------------------------------------------------------------------------------//
    Scene* s = SceneManager::Instance()->AddScene("Play", true);
    s = SceneManager::Instance()->GetScene("Play");

    Entity* e = s->AddEntity("Player");

    Component* transform = e->AddComponent("RigidBodyComponent");

    Component* node_collider = e->AddComponent("ColliderComponent");

    std::cout << SceneManager::Instance()->GetScene("Play")->GetEntity("Player")->HasComponent("RigidBodyComponent") << "\n";
    std::cout << SceneManager::Instance()->GetScene("Play")->GetEntity("Player")->HasComponent("ColliderComponent") << "\n";

    return 0;
}