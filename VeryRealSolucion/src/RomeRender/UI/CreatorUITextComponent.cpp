#include "CreatorUITextComponent.h"
#include "UITextComponent.h"
#include <string>
using namespace VeryReal;
Component* CreatorUITextComponent::CreatorSpecificComponent() { return new UITextComponent(); }

std::pair<bool,std::string> CreatorUITextComponent::SpecificInitComponent(Component* c) {
    UITextComponent* a = static_cast<UITextComponent*>(c);
    std::string name, font, caption;
    int zOrder;
    float charHeight;
    VeryReal::Vector3 color, colorTop, colorBottom;

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

#pragma region Font

    if (parameters_map.find("font") != parameters_map.end()) {
        if (std::holds_alternative<std::string>(parameters_map.at("font")->GetVariant())) {
            font = std::get<std::string>(parameters_map.at("font")->GetVariant());
        }
        else {
            std::cout << "No se ha especificado ningun valor para font este sera seteado por defecto" << std::endl;
            font = " ";
        }
    }
    else {
        std::cout << "No existe ningun parametro font este sera seteado por defecto" << std::endl;
        font = " ";
    }
#pragma endregion

#pragma region Caption

    if (parameters_map.find("caption") != parameters_map.end()) {
        if (std::holds_alternative<std::string>(parameters_map.at("caption")->GetVariant())) {
            caption = std::get<std::string>(parameters_map.at("caption")->GetVariant());
        }
        else {
            std::cout << "No se ha especificado ningun valor para caption este sera seteado por defecto" << std::endl;
            caption = " ";
        }
    }
    else {
        std::cout << "No existe ningun parametro caption este sera seteado por defecto" << std::endl;
        caption = " ";
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

#pragma region CharHeight

    if (parameters_map.find("charHeight") != parameters_map.end()) {
        if (std::holds_alternative<float>(parameters_map.at("charHeight")->GetVariant())) {
            charHeight = std::get<float>(parameters_map.at("charHeight")->GetVariant());
        }
        else {
            std::cout << "No se ha especificado ningun valor para charHeight este sera seteado por defecto" << std::endl;
            charHeight = 0;
        }
    }
    else {
        std::cout << "No existe ningun parametro charHeight este sera seteado por defecto" << std::endl;
        charHeight = 0;
    }
#pragma endregion
    if (parameters_map.find("color") != parameters_map.end()) {
        if (std::holds_alternative<VeryReal::Vector3>(parameters_map.at("color")->GetVariant())) {
            color = std::get<VeryReal::Vector3>(parameters_map.at("color")->GetVariant());
        }
        return a->InitComponent(name, font, zOrder, charHeight, color, caption);
    }
    else {
        if (std::holds_alternative<VeryReal::Vector3>(parameters_map.at("colorTop")->GetVariant())) {
            colorTop = std::get<VeryReal::Vector3>(parameters_map.at("colorTop")->GetVariant());
        }
        if (std::holds_alternative<VeryReal::Vector3>(parameters_map.at("colorBottom")->GetVariant())) {
            colorBottom = std::get<VeryReal::Vector3>(parameters_map.at("colorBottom")->GetVariant());
        }
        return a->InitComponent(name, font, zOrder, charHeight, colorBottom, colorTop, caption);
    }
}

std::pair<bool,std::string> CreatorUITextComponent::SpecificInitComponentByCopy(Component* c, Component* other) {
    UITextComponent* a = static_cast<UITextComponent*>(c);
    UITextComponent* copia = static_cast<UITextComponent*>(other);

    bool b;
    if (copia->GetNormalOrTopBottom()) {
        return a->InitComponent(copia->GetTextName(), copia->GetFontName(), copia->GetZOrder(), copia->GetCharHeight(), copia->GetColor(), 
            copia->GetTextCaption());
    }
    else {
        return a->InitComponent(copia->GetTextName(), copia->GetFontName(), copia->GetZOrder(), copia->GetCharHeight(), copia->GetColorBottom(),
            copia->GetColorTop(), copia->GetTextCaption());
    }
}