#include "CreatorAnimatorComponent.h"
#include "AnimatorComponent.h"
#include <string>
using namespace VeryReal;
Component* CreatorAnimatorComponent::CreatorSpecificComponent() { return new AnimatorComponent(); }

void CreatorAnimatorComponent::SpecificInitComponent(Component* c) {
    AnimatorComponent* a = static_cast<AnimatorComponent*>(c);
    std::string name;

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
    /*  if (std::holds_alternative<std::string>(parameters_map.at("name")->GetVariant())) {
        name = std::get<std::string>(parameters_map.at("name")->GetVariant());
    }*/
    bool b = a->InitComponent(name);
    if (!b) {
        //Gestionar error
    }
}

void CreatorAnimatorComponent::SpecificInitComponentByCopy(Component* c, Component* other) { 

}