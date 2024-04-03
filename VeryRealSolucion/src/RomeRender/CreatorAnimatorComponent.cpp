#include "CreatorAnimatorComponent.h"
#include "AnimatorComponent.h"
#include <string>
using namespace VeryReal;
Component* CreatorAnimatorComponent::CreatorSpecificComponent() { 
    return new AnimatorComponent();
}

void CreatorAnimatorComponent::SpecificInitComponent(Component* c) {
    AnimatorComponent* a = static_cast<AnimatorComponent*>(c);
    std::string name;
    if (std::holds_alternative<std::string>(parameters_map.at("name")->GetVariant())) {
        name = std::get<std::string>(parameters_map.at("name")->GetVariant());
    }
    bool b = a->InitComponent(name);
    if (!b) {
        //Gestionar error
    }
}