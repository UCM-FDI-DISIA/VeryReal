#include "CreatorCameraComponent.h"
#include "CameraComponent.h"
using namespace VeryReal;
Component* CreatorCameraComponent::CreatorSpecificComponent() { return new CameraComponent(); }

void CreatorCameraComponent::SpecificInitComponent(Component* c) {
    CameraComponent* cam = static_cast<CameraComponent*>(c);
    std::string name;
    Vector3 offset;
    Vector3 color;
    float alfa = 0;

#pragma region Name

    if (parameters_map.find("name") != parameters_map.end()) {
        if (std::holds_alternative<std::string>(parameters_map.at("name")->GetVariant())) {
            name = std::get<std::string>(parameters_map.at("name")->GetVariant());
        }
        else {
            std::cout << "No se ha especificado ningun valor para name este sera seteado por defecto" << std::endl;
            name = " ";
        }
    }
    else {
        std::cout << "No existe ningun parametro name este sera seteado por defecto" << std::endl;
        name = " ";
    }
#pragma endregion

#pragma region Color

    if (parameters_map.find("color") != parameters_map.end()) {
        if (std::holds_alternative<Vector3>(parameters_map.at("color")->GetVariant())) {
            color = std::get<Vector3>(parameters_map.at("color")->GetVariant());
        }
        else {
            std::cout << "No se ha especificado ningun valor para color este sera seteado por defecto" << std::endl;
            color = Vector3(0, 0, 0);
        }
    }
    else {
        std::cout << "No existe ningun parametro color este sera seteado por defecto" << std::endl;
        color = Vector3(0, 0, 0);
    }
#pragma endregion

#pragma region Alfa

    if (parameters_map.find("alfa") != parameters_map.end()) {
        if (std::holds_alternative<float>(parameters_map.at("alfa")->GetVariant())) {
            alfa = std::get<float>(parameters_map.at("alfa")->GetVariant());
        }
        else {
            std::cout << "No se ha especificado ningun valor para alfa este sera seteado por defecto" << std::endl;
            alfa = 1.0f;
        }
    }
    else {
        std::cout << "No existe ningun parametro alfa este sera seteado por defecto" << std::endl;
        alfa = 1.0f;
    }
#pragma endregion

#pragma region Offset

    if (parameters_map.find("offset") != parameters_map.end()) {
        if (std::holds_alternative<Vector3>(parameters_map.at("offset")->GetVariant())) {
            offset = std::get<Vector3>(parameters_map.at("offset")->GetVariant());
        }
        else {
            std::cout << "No se ha especificado ningun valor para offset este sera seteado por defecto" << std::endl;
            offset = Vector3(0, 0, 0);
        }
    }
    else {
        std::cout << "No existe ningun parametro offset este sera seteado por defecto" << std::endl;
        offset = Vector3(0, 0, 0);
    }
#pragma endregion


    /* if (std::holds_alternative<std::string>(parameters_map.at("name")->GetVariant())) {
        name = std::get<std::string>(parameters_map.at("name")->GetVariant());
    }
    if (std::holds_alternative<Vector3>(parameters_map.at("color")->GetVariant())) {
        color = std::get<Vector3>(parameters_map.at("color")->GetVariant());
    }
    if (std::holds_alternative<float>(parameters_map.at("alfa")->GetVariant())) {
        alfa = std::get<float>(parameters_map.at("alfa")->GetVariant());
    }
    if (std::holds_alternative<Vector3>(parameters_map.at("offset")->GetVariant())) {
        offset = std::get<Vector3>(parameters_map.at("offset")->GetVariant());
    }*/
    bool b = cam->InitComponent(name, color, alfa, offset);
    if (!b) {
        // Gestion de error
    }
}
