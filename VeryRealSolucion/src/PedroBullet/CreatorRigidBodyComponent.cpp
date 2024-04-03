#include "CreatorRigidBodyComponent.h"
#include "RigidBodyComponent.h"
using namespace VeryReal;
Component* CreatorRigidBodyComponent::CreatorSpecificComponent() { 
    return new RigidBodyComponent();
}

void CreatorRigidBodyComponent::SpecificInitComponent(Component* c) {
    RigidBodyComponent* r = static_cast<RigidBodyComponent*>(c);


    /*RigidBodyComponent(PBShapes shapeType, float mass, float friction = 0.5f, float restitution = 0.0f, 
		PBMovementType movementType = MOVEMENT_TYPE_DYNAMIC, bool trigger = false);*/

    //recibir la forma, quizas formas de objetos tienen que ir en aquitectura básica, hablar con el grupo
    //mirar movimiento tambien
    //de momento estas dos lineas temporales para que no de error hasta que lo hablemos
    PBShapes shapeType = SHAPES_BOX;
    PBMovementType movementType = MOVEMENT_TYPE_DYNAMIC;
    float mass, friction, restitution;
    bool trigger;
    if (std::holds_alternative<float>(parameters_map.at("mass")->GetVariant())) {
        mass = std::get<float>(parameters_map.at("mass")->GetVariant());
    }
    if (std::holds_alternative<float>(parameters_map.at("friction")->GetVariant())) {
        friction = std::get<float>(parameters_map.at("friction")->GetVariant());
    }
    else {
        friction = 0.5f;
    }
    if (std::holds_alternative<float>(parameters_map.at("restitution")->GetVariant())) {
        restitution = std::get<float>(parameters_map.at("restitution")->GetVariant());
    }
    else {
        restitution = 0.0f;
    }
    if (std::holds_alternative<bool>(parameters_map.at("trigger")->GetVariant())) {
        trigger = std::get<bool>(parameters_map.at("trigger")->GetVariant());
    }
    else {
        trigger = false;
    }
    bool b = r->InitComponent(shapeType, mass, friction, restitution, movementType, trigger);
    if (!b) {
        // Gestionar error
    }
}