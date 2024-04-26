#include "CreatorCameraComponent.h"
#include "CameraComponent.h"
using namespace VeryReal;
Component* CreatorCameraComponent::CreatorSpecificComponent() { 
    return new CameraComponent();
}

void CreatorCameraComponent::SpecificInitComponent(Component* c) {
    CameraComponent* cam = static_cast<CameraComponent*>(c);
    std::string name;
    Vector3  offset;
    Vector4 color;
    if (std::holds_alternative<std::string>(parameters_map.at("name")->GetVariant())) {
        name = std::get<std::string>(parameters_map.at("name")->GetVariant());
    }
    if (std::holds_alternative<Vector4>(parameters_map.at("color")->GetVariant())) {
        color = std::get<Vector4>(parameters_map.at("color")->GetVariant());
    }
    if (std::holds_alternative<Vector3>(parameters_map.at("offset")->GetVariant())) {
        offset = std::get<Vector3>(parameters_map.at("offset")->GetVariant());
    }
    bool b = cam->InitComponent(name, color, offset);
    if (!b) {
        // Gestion de error
    }
}
