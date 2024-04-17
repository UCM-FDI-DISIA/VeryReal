#include "CreatorUIProgressBarComponent.h"
#include "UIProgressBarComponent.h"
using namespace VeryReal;
Component* CreatorUIProgressBarComponent::CreatorSpecificComponent() { return new UIProgressBarComponent(); }

void CreatorUIProgressBarComponent::SpecificInitComponent(Component* c) {
    UIProgressBarComponent* progressbar = static_cast<UIProgressBarComponent*>(c);
     double maximo, progres;
    if (std::holds_alternative<double>(parameters_map.at("maximo")->GetVariant())) {
         maximo = std::get<double>(parameters_map.at("maximo")->GetVariant());
    }
    if (std::holds_alternative<double>(parameters_map.at("progres")->GetVariant())) {
        progres = std::get<double>(parameters_map.at("progres")->GetVariant());
    }
   
    bool b = progressbar->InitComponent(maximo, progres);
    if (!b) {
        // Gestion de error
    }
}
