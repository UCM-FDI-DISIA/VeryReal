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
//    PBShapes shapeType;
//    PBMovementType movementType;
//    float mass, friction, restitution;
//    Vector3 size;
//    int mask, group;
//    bool trigger;
//    if (std::holds_alternative<PBShapes>(parameters_map.at("shapeType")->GetVariant())) {
//        shapeType = std::get<PBShapes>(parameters_map.at("shapeType")->GetVariant());
//    }
//    else {
//        shapeType = PBShapes(0);
//    }
//    if (std::holds_alternative<PBMovementType>(parameters_map.at("movementType")->GetVariant())) {
//        movementType = std::get<PBMovementType>(parameters_map.at("movementType")->GetVariant());
//    }
//    else {
//        movementType = PBMovementType(0);
//    }
//    if (std::holds_alternative<float>(parameters_map.at("mass")->GetVariant())) {
//        mass = std::get<float>(parameters_map.at("mass")->GetVariant());
//    }
//    else {
//        mass = 0.5f;
//    }
//    if (std::holds_alternative<float>(parameters_map.at("friction")->GetVariant())) {
//        friction = std::get<float>(parameters_map.at("friction")->GetVariant());
//    }
//    else {
//        friction = 0.5f;
//    }
//    if (std::holds_alternative<float>(parameters_map.at("restitution")->GetVariant())) {
//        restitution = std::get<float>(parameters_map.at("restitution")->GetVariant());
//    }
//    else {
//        restitution = 0.0f;
//    }
//    if (std::holds_alternative<bool>(parameters_map.at("trigger")->GetVariant())) {
//        trigger = std::get<bool>(parameters_map.at("trigger")->GetVariant());
//    }
//    else {
//        trigger = false;
//    }
//    if (std::holds_alternative<Vector3>(parameters_map.at("size")->GetVariant())) {
//        size = std::get<Vector3>(parameters_map.at("size")->GetVariant());
//    }
//    else {
//        size = Vector3{1,1,1};
//    }
//    if (std::holds_alternative<int>(parameters_map.at("mask")->GetVariant())) {
//        mask = std::get<int>(parameters_map.at("mask")->GetVariant());
//    }
//    else {
//        mask = 1;
//    }
//    if (std::holds_alternative<int>(parameters_map.at("group")->GetVariant())) {
//        group = std::get<int>(parameters_map.at("group")->GetVariant());
//    }
//    else {
//        group = 1;
//    }
//    bool b = r->InitComponent(shapeType, mass, friction, restitution, movementType, trigger, size, mask, group);
//    if (!b) {
//        // Gestionar error
//    }
}
//mascara y grupo-------
//grupos: 1, 2, 4, 8, 16
//mascara: suma de los grupos que colisionan. ej:3 colisiona con el grupo 1 y 2.


