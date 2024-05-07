#include "CreatorUISpriteRenderComponent.h"
#include "UISpriteRenderComponent.h"
#include <string>
using namespace VeryReal;
Component* CreatorUISpriteRenderComponent::CreatorSpecificComponent() { return new UISpriteRendererComponent(); }

std::pair<bool,std::string> CreatorUISpriteRenderComponent::SpecificInitComponent(Component* c) {
    UISpriteRendererComponent* a = static_cast<UISpriteRendererComponent*>(c);
    std::string name, material;
    int zOrder;
#pragma region Material

    if (parameters_map.find("material") != parameters_map.end()) {
        if (std::holds_alternative<std::string>(parameters_map.at("material")->GetVariant())) {
            material = std::get<std::string>(parameters_map.at("material")->GetVariant());
        }
        else {
            std::cout << "No se ha especificado ningun valor para material este sera seteado por defecto" << std::endl;
            material = " ";
        }
    }
    else {
        std::cout << "No existe ningun parametro material este sera seteado por defecto" << std::endl;
        material = " ";
    }
#pragma endregion

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

#pragma region zOrder

    if (parameters_map.find("zOrder") != parameters_map.end()) {
        if (std::holds_alternative<int>(parameters_map.at("zOrder")->GetVariant())) {
            zOrder = std::get<int>(parameters_map.at("zOrder")->GetVariant());
        }
        else {
            std::cout << "No se ha especificado ningun valor para zOrder este sera seteado por defecto" << std::endl;
            zOrder = 0;
        }
    }
    else {
        std::cout << "No existe ningun parametro zOrder este sera seteado por defecto" << std::endl;
        zOrder = 0;
    }
#pragma endregion
    return a->InitComponent(name, material, zOrder);
}

std::pair<bool, std::string> CreatorUISpriteRenderComponent::SpecificInitComponentByCopy(Component* c, Component* other) {
    UISpriteRendererComponent* a = static_cast<UISpriteRendererComponent*>(c);
    UISpriteRendererComponent* copia = static_cast<UISpriteRendererComponent*>(other);

    return a->InitComponent(copia->GetSpriteName(), copia->GetMaterialName(), copia->GetZOrder());
}