#include "UIProgressBarComponent.h"
#include <string>
#include "CreatorUIProgressBarComponent.h"
using namespace VeryReal;

Component* VeryReal::CreatorUIProgressBarComponent::CreatorSpecificComponent() { 
    return new UIProgressBarComponent; 
}

void VeryReal::CreatorUIProgressBarComponent::SpecificInitComponent(Component* c) { 
    UIProgressBarComponent* progressbar = static_cast<UIProgressBarComponent*>(c);
    double maximo, progres;
    std::string progressBarName, frameMaterial, contentMaterial;
    int zOrder;

    if (std::holds_alternative<float>(parameters_map.at("maximo")->GetVariant())) {
        maximo = std::get<float>(parameters_map.at("maximo")->GetVariant());
    }
    if (std::holds_alternative<float>(parameters_map.at("progres")->GetVariant())) {
        progres = std::get<float>(parameters_map.at("progres")->GetVariant());
    }
    if (std::holds_alternative<std::string>(parameters_map.at("progressBarName")->GetVariant())) {
        progressBarName = std::get<std::string>(parameters_map.at("progressBarName")->GetVariant());
    }
    if (std::holds_alternative<std::string>(parameters_map.at("frameMaterial")->GetVariant())) {
        frameMaterial = std::get<std::string>(parameters_map.at("frameMaterial")->GetVariant());
    }
    if (std::holds_alternative<std::string>(parameters_map.at("contentMaterial")->GetVariant())) {
        contentMaterial = std::get<std::string>(parameters_map.at("contentMaterial")->GetVariant());
    }
    if (std::holds_alternative<int>(parameters_map.at("zOrder")->GetVariant())) {
        zOrder = std::get<int>(parameters_map.at("zOrder")->GetVariant());
    }

    bool b = progressbar->InitComponent(maximo, progres, progressBarName, frameMaterial, contentMaterial, zOrder);
    if (!b) {
        //Gestionar error
    }
}
