#include "CreatorUITextComponent.h"
#include "UITextComponent.h"
#include <string>
using namespace VeryReal;
Component* CreatorUITextComponent::CreatorSpecificComponent() { 
    return new UITextComponent(); }

void CreatorUITextComponent::SpecificInitComponent(Component* c) {
    UITextComponent* a = static_cast<UITextComponent*>(c);
    std::string name, font, caption;
    int zOrder;
    float charHeight;
    VeryReal::Vector3 color, colorTop, colorBottom;
    if (std::holds_alternative<std::string>(parameters_map.at("name")->GetVariant())) {
        name = std::get<std::string>(parameters_map.at("name")->GetVariant());
    }
    if (std::holds_alternative<std::string>(parameters_map.at("font")->GetVariant())) {
        font = std::get<std::string>(parameters_map.at("font")->GetVariant());
    }
    if (std::holds_alternative<std::string>(parameters_map.at("caption")->GetVariant())) {
        caption = std::get<std::string>(parameters_map.at("caption")->GetVariant());
    }
    if (std::holds_alternative<int>(parameters_map.at("zOrder")->GetVariant())) {
        zOrder = std::get<int>(parameters_map.at("zOrder")->GetVariant());
    }
    if (std::holds_alternative<float>(parameters_map.at("charHeight")->GetVariant())) {
        charHeight = std::get<float>(parameters_map.at("charHeight")->GetVariant());
    }
    
    bool b;
    if (parameters_map.count("color")) {
        if (std::holds_alternative<VeryReal::Vector3>(parameters_map.at("color")->GetVariant())) {
            color = std::get<VeryReal::Vector3>(parameters_map.at("color")->GetVariant());
        }
        b = a->InitComponent(name, font, zOrder, charHeight, color, caption);
    }
    else {
        if (std::holds_alternative<VeryReal::Vector3>(parameters_map.at("colorTop")->GetVariant())) {
            colorTop = std::get<VeryReal::Vector3>(parameters_map.at("colorTop")->GetVariant());
        }
        if (std::holds_alternative<VeryReal::Vector3>(parameters_map.at("colorBottom")->GetVariant())) {
            colorBottom = std::get<VeryReal::Vector3>(parameters_map.at("colorBottom")->GetVariant());
        }
        b = a->InitComponent(name, font, zOrder, charHeight, colorBottom, colorTop, caption);
    }
    
    if (!b) {
        //Gestionar error
    }
}