#include "CreatorAnimatorComponent.h"
#include "AnimatorComponent.h"
#include <string>
using namespace VeryReal;
Component* CreatorAnimatorComponent::CreatorSpecificComponent() {
    std::string name;
    AnimatorComponent* a = new AnimatorComponent();

    if (std::holds_alternative<std::string>(parameters_map.at("name")->GetVariant())) {
        name = std::get<std::string>(parameters_map.at("name")->GetVariant());
    }
    bool b= a->InitComponent(name);
    if(!b){
        return nullptr;
    }
    return a;
}