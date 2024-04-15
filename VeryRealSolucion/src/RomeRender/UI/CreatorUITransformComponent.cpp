#include "CreatorUITransformComponent.h"
#include "UITransformComponent.h"
#include <string>
using namespace VeryReal;
Component* CreatorUITransformComponent::CreatorSpecificComponent() { 
    return new UITransformComponent();
}

void CreatorUITransformComponent::SpecificInitComponent(Component* c) {
    UITransformComponent* a = static_cast<UITransformComponent*>(c);
    VeryReal::Vector2 pos, scale;
    if (std::holds_alternative<VeryReal::Vector2>(parameters_map.at("position")->GetVariant())) {
        pos = std::get<VeryReal::Vector2>(parameters_map.at("position")->GetVariant());
    }
    if (std::holds_alternative<VeryReal::Vector2>(parameters_map.at("scale")->GetVariant())) {
        scale = std::get<VeryReal::Vector2>(parameters_map.at("scale")->GetVariant());
    }
    
    bool b = a->InitComponent(pos, scale);
    if (!b) {
        //Gestionar error
    }
}