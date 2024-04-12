#include "CreatorUISpriteRenderComponent.h"
#include "UISpriteRenderComponent.h"
#include <string>
using namespace VeryReal;
Component* CreatorUISpriteRenderComponent::CreatorSpecificComponent() { 
    return new UiSpriteRenderer();
}

void CreatorUISpriteRenderComponent::SpecificInitComponent(Component* c) {
    UiSpriteRenderer* a = static_cast<UiSpriteRenderer*>(c);
    std::string name, material;
    float zOrder;
    if (std::holds_alternative<std::string>(parameters_map.at("name")->GetVariant())) {
        name = std::get<std::string>(parameters_map.at("name")->GetVariant());
    }
    if (std::holds_alternative<std::string>(parameters_map.at("material")->GetVariant())) {
        material = std::get<std::string>(parameters_map.at("material")->GetVariant());
    }
    if (std::holds_alternative<float>(parameters_map.at("zOrder")->GetVariant())) {
        zOrder = std::get<float>(parameters_map.at("zOrder")->GetVariant());
    }
    
    bool b = a->InitComponent(name, material, zOrder);
    if (!b) {
        //Gestionar error
    }
}