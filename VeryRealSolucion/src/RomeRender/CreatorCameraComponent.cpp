#include "CreatorCameraComponent.h"
#include "CameraComponent.h"
using namespace VeryReal;
Component* CreatorCameraComponent::CreatorSpecificComponent() {
    CameraComponent* c = new CameraComponent();
    std::string name;
    Vector3 color, offset;
    if (std::holds_alternative<std::string>(parameters_map.at("name")->GetVariant())) {
        name = std::get<std::string>(parameters_map.at("name")->GetVariant());
    }
    if (std::holds_alternative<Vector3>(parameters_map.at("color")->GetVariant())) {
        color = std::get<Vector3>(parameters_map.at("color")->GetVariant());
    }
    if (std::holds_alternative<Vector3>(parameters_map.at("offset")->GetVariant())) {
        offset = std::get<Vector3>(parameters_map.at("offset")->GetVariant());
    }
    bool b=c->InitComponent(name, color, offset);
    if(!b){
        return nullptr;
    }
    return c;
}
