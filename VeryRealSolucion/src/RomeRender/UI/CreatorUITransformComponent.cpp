#include "CreatorUITransformComponent.h"
#include "UITransformComponent.h"
#include <string>
using namespace VeryReal;
Component* CreatorUITransformComponent::CreatorSpecificComponent() { return new UITransformComponent(); }

std::pair<bool,std::string> CreatorUITransformComponent::SpecificInitComponent(Component* c) {
    UITransformComponent* a = static_cast<UITransformComponent*>(c);
    VeryReal::Vector2 pos, scale;
    bool hidden;

#pragma region Position

    if (parameters_map.find("position") != parameters_map.end()) {
        if (std::holds_alternative<VeryReal::Vector2>(parameters_map.at("position").GetVariant())) {
            pos = std::get<VeryReal::Vector2>(parameters_map.at("position").GetVariant());
        }
        else {
            std::cout << "No se ha especificado ningun valor para position este sera seteado por defecto" << std::endl;
            pos = Vector2(0, 0);
        }
    }
    else {
        std::cout << "No existe ningun parametro position este sera seteado por defecto" << std::endl;
        pos = Vector2(0, 0);
    }
#pragma endregion

#pragma region Scale

    if (parameters_map.find("scale") != parameters_map.end()) {
        if (std::holds_alternative<VeryReal::Vector2>(parameters_map.at("scale").GetVariant())) {
            scale = std::get<VeryReal::Vector2>(parameters_map.at("scale").GetVariant());
        }
        else {
            std::cout << "No se ha especificado ningun valor para scale este sera seteado por defecto" << std::endl;
            scale = Vector2(1, 1);
        }
    }
    else {
        std::cout << "No existe ningun parametro scale este sera seteado por defecto" << std::endl;
        scale = Vector2(0, 0);
    }
#pragma endregion

#pragma region Hidden

    if (parameters_map.find("hidden") != parameters_map.end()) {
        if (std::holds_alternative<bool>(parameters_map.at("hidden").GetVariant())) {
            hidden = std::get<bool>(parameters_map.at("hidden").GetVariant());
        }
        else {
            std::cout << "No se ha especificado ningun valor para hidden este sera seteado por defecto" << std::endl;
            hidden = false;
        }
    }
    else {
        std::cout << "No existe ningun parametro hidden este sera seteado por defecto" << std::endl;
        hidden = false;
    }
#pragma endregion
    return a->InitComponent(pos, scale, hidden);
    
}

std::pair<bool, std::string> CreatorUITransformComponent::SpecificInitComponentByCopy(Component* c, Component* other) 
{ return {true, ""}; }