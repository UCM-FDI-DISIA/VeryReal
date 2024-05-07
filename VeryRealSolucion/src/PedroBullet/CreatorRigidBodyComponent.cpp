#include "CreatorRigidBodyComponent.h"
#include "RigidBodyComponent.h"
using namespace VeryReal;
Component* CreatorRigidBodyComponent::CreatorSpecificComponent() { return new RigidBodyComponent(); }

std::pair<bool,std::string> CreatorRigidBodyComponent::SpecificInitComponent(Component* c) {
    RigidBodyComponent* r = static_cast<RigidBodyComponent*>(c);
    int shapeType;
    int movementType;
    float mass, friction, restitution;
    Vector3 size;
    int mask, group;
    bool trigger;
#pragma region ShapeType

    if (parameters_map.find("shapeType") != parameters_map.end()) {
        if (std::holds_alternative<int>(parameters_map.at("shapeType")->GetVariant())) {
            shapeType = std::get<int>(parameters_map.at("shapeType")->GetVariant());
        }
        else {
            std::cout << "No se ha especificado ningun valor para shapeType este sera seteado por defecto" << std::endl;
            shapeType = 0;
        }
    }
    else {
        std::cout << "No existe ningun parametro shapeType este sera seteado por defecto" << std::endl;
        shapeType = 0;
    }
#pragma endregion
#pragma region MovementType

    if (parameters_map.find("movementType") != parameters_map.end()) {
        if (std::holds_alternative<int>(parameters_map.at("movementType")->GetVariant())) {
            movementType = std::get<int>(parameters_map.at("movementType")->GetVariant());
        }
        else {
            std::cout << "No se ha especificado ningun valor para movementType este sera seteado por defecto" << std::endl;
            movementType = 0;
        }
    }
    else {
        std::cout << "No existe ningun parametro movementType este sera seteado por defecto" << std::endl;
        movementType = 0;
    }
#pragma endregion
#pragma region Mass

    if (parameters_map.find("mass") != parameters_map.end()) {
        if (std::holds_alternative<float>(parameters_map.at("mass")->GetVariant())) {
            mass = std::get<float>(parameters_map.at("mass")->GetVariant());
        }
        else {
            std::cout << "No se ha especificado ningun valor para mass este sera seteado por defecto" << std::endl;
            mass = 0;
        }
    }
    else {
        std::cout << "No existe ningun parametro mass este sera seteado por defecto" << std::endl;
        mass = 0.5f;
    }
#pragma endregion
#pragma region Friction

    if (parameters_map.find("friction") != parameters_map.end()) {
        if (std::holds_alternative<float>(parameters_map.at("friction")->GetVariant())) {
            friction = std::get<float>(parameters_map.at("friction")->GetVariant());
        }
        else {
            std::cout << "No se ha especificado ningun valor para friction este sera seteado por defecto" << std::endl;
            friction = 0.1;
        }
    }
    else {
        std::cout << "No existe ningun parametro friction este sera seteado por defecto" << std::endl;
        friction = 0.1f;
    }
#pragma endregion
#pragma region Restitution

    if (parameters_map.find("restitution") != parameters_map.end()) {
        if (std::holds_alternative<float>(parameters_map.at("restitution")->GetVariant())) {
            restitution = std::get<float>(parameters_map.at("restitution")->GetVariant());
        }
        else {
            std::cout << "No se ha especificado ningun valor para restitution este sera seteado por defecto" << std::endl;
            restitution = 0.0f;
        }
    }
    else {
        std::cout << "No existe ningun parametro restitution este sera seteado por defecto" << std::endl;
        restitution = 0.0f;
    }
#pragma endregion
#pragma region Trigger

    if (parameters_map.find("trigger") != parameters_map.end()) {
        if (std::holds_alternative<bool>(parameters_map.at("trigger")->GetVariant())) {
            trigger = std::get<bool>(parameters_map.at("trigger")->GetVariant());
        }
        else {
            std::cout << "No se ha especificado ningun valor para trigger este sera seteado por defecto" << std::endl;
            trigger = false;
        }
    }
    else {
        std::cout << "No existe ningun parametro trigger este sera seteado por defecto" << std::endl;
        trigger = false;
    }
#pragma endregion
#pragma region Size

    if (parameters_map.find("size") != parameters_map.end()) {
        if (std::holds_alternative<Vector3>(parameters_map.at("size")->GetVariant())) {
            size = std::get<Vector3>(parameters_map.at("size")->GetVariant());
        }
        else {
            std::cout << "No se ha especificado ningun valor para size este sera seteado por defecto" << std::endl;
            size = Vector3{1, 1, 1};
        }
    }
    else {
        std::cout << "No existe ningun parametro size este sera seteado por defecto" << std::endl;
        size = Vector3{1, 1, 1};
    }
#pragma endregion
#pragma region Mask

    if (parameters_map.find("mask") != parameters_map.end()) {
        if (std::holds_alternative<int>(parameters_map.at("mask")->GetVariant())) {
            mask = std::get<int>(parameters_map.at("mask")->GetVariant());
        }
        else {
            std::cout << "No se ha especificado ningun valor para mask este sera seteado por defecto" << std::endl;
            mask = 2;
        }
    }
    else {
        std::cout << "No existe ningun parametro mask este sera seteado por defecto" << std::endl;
        mask = 2;
    }
#pragma endregion
#pragma region Group

    if (parameters_map.find("group") != parameters_map.end()) {
        if (std::holds_alternative<int>(parameters_map.at("group")->GetVariant())) {
            group = std::get<int>(parameters_map.at("group")->GetVariant());
        }
        else {
            std::cout << "No se ha especificado ningun valor para group este sera seteado por defecto" << std::endl;
            group = 1;
        }
    }
    else {
        std::cout << "No existe ningun parametro group este sera seteado por defecto" << std::endl;
        group = 1;
    }
#pragma endregion
    return r->InitComponent(shapeType, mass, friction, restitution, movementType, trigger, size, mask, group);
}

std::pair<bool, std::string> CreatorRigidBodyComponent::SpecificInitComponentByCopy(Component* c, Component* other) {
    RigidBodyComponent* r = static_cast<RigidBodyComponent*>(c);
    RigidBodyComponent* copia = static_cast<RigidBodyComponent*>(other);

    return r->InitComponent(copia->getShapeTypeVar(), copia->GetMass(), copia->GetFriction(), copia->GetRestitution(), copia->GetMovementType(),
                              copia->GetIsTrigger(), copia->GetSizeVar(), copia->getMask(), copia->getGroup());
}