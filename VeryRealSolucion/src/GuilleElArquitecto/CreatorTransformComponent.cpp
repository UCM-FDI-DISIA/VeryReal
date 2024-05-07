#include "CreatorTransformComponent.h"
#include "TransformComponent.h"
using namespace VeryReal;

Component* CreatorTransformComponent::CreatorSpecificComponent() { return new TransformComponent(); }

std::pair<bool, std::string> CreatorTransformComponent::SpecificInitComponent(Component* c) {
    Vector3 position, rotation, scale;
    int a = 0;
    TransformComponent* t = static_cast<TransformComponent*>(c);

#pragma region Position

    if (parameters_map.find("position") != parameters_map.end()) {
        if (std::holds_alternative<Vector3>(parameters_map.at("position")->GetVariant())) {
            position = std::get<Vector3>(parameters_map.at("position")->GetVariant());
        }
        else {
            std::cout << "No se ha especificado ningun valor para position este sera seteado por defecto" << std::endl;
            position = Vector3(0, 0, 0);
        }
    }
    else {
        std::cout << "No existe ningun parametro position este sera seteado por defecto" << std::endl;
        position = Vector3(0, 0, 0);
    }
#pragma endregion
#pragma region Rotation

    if (parameters_map.find("rotation") != parameters_map.end()) {
        if (std::holds_alternative<Vector3>(parameters_map.at("rotation")->GetVariant())) {
            rotation = std::get<Vector3>(parameters_map.at("rotation")->GetVariant());
        }
        else {
            std::cout << "No se ha especificado ningun valor para rotation este sera seteado por defecto" << std::endl;
            rotation = Vector3(0, 0, 0);
        }
    }
    else {
        std::cout << "No existe ningun parametro rotation este sera seteado por defecto" << std::endl;
        rotation = Vector3(0, 0, 0);
    }
#pragma endregion
#pragma region Scale

    if (parameters_map.find("scale") != parameters_map.end()) {
        if (std::holds_alternative<Vector3>(parameters_map.at("scale")->GetVariant())) {
            scale = std::get<Vector3>(parameters_map.at("scale")->GetVariant());
        }
        else {
            std::cout << "No se ha especificado ningun valor para scale este sera seteado por defecto" << std::endl;
            scale = Vector3(1, 1, 1);
        }
    }
    else {
        std::cout << "No existe ningun parametro scale este sera seteado por defecto" << std::endl;
        scale = Vector3(1, 1, 1);
    }
#pragma endregion
    return t->InitComponent(position, rotation, scale); 
}

std::pair<bool, std::string> CreatorTransformComponent::SpecificInitComponentByCopy(Component* c, Component* other) {
    Vector3 position, rotation, scale;
    int a = 0;
    TransformComponent* t = static_cast<TransformComponent*>(c);
    TransformComponent* copia = static_cast<TransformComponent*>(other);
    return t->InitComponent(copia->GetPosition(), copia->GetRotationInit(), copia->GetScale());
}