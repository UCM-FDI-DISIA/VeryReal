#include "CreatorTransformComponent.h"
#include "TransformComponent.h"
using namespace VeryReal;

Component* CreatorTransformComponent::CreatorSpecificComponent() { return new TransformComponent(); }

void CreatorTransformComponent::SpecificInitComponent(Component* c) {
    Vector3 position, rotation, scale;
    int a = 0;
    TransformComponent* t = static_cast<TransformComponent*>(c);
//#pragma region Aux
//
//        if (parameters_map.find("aux") != parameters_map.end()) {
//            if (std::holds_alternative<int>(parameters_map.at("aux")->GetVariant())) {
//                a = std::get<int>(parameters_map.at("aux")->GetVariant());
//            }
//            else {
//                std::cout << "No se ha especificado ningun valor para aux este sera seteado por defecto" << std::endl;
//                a = 0;
//            }
//        }
//        else {
//            std::cout << "No existe ningun parametro aux este sera seteado por defecto" << std::endl;
//            a = 0;
//        }
//#pragma endregion
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
    bool b = t->InitComponent(a, position, rotation, scale);
    if (!b) {
    }   //FALTA GESTION DE ERRORES
}