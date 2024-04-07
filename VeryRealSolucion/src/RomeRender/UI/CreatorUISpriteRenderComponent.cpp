#include "CreatorUISpriteRenderComponent.h"
#include "UISpriteRenderComponent.h"
#include <string>
using namespace VeryReal;
Component* CreatorUISpriteRenderComponent::CreatorSpecificComponent() { 
    return new UiSpriteRenderer();
}

void CreatorUISpriteRenderComponent::SpecificInitComponent(Component* c) {
    UiSpriteRenderer* a = static_cast<UiSpriteRenderer*>(c);
    std::string name;
   /* if (std::holds_alternative<std::string>(parameters_map.at("name")->GetVariant())) {
        name = std::get<std::string>(parameters_map.at("name")->GetVariant());
    }*/
    bool b = a->InitComponent();
    if (!b) {
        //Gestionar error
    }
}