#include "CreatorUIButtonComponent.h"
#include "UIButtonComponent.h"
using namespace VeryReal;
Component* CreatorButtonComponent::CreatorSpecificComponent() { return new UIButtonComponent(); }

std::pair<bool, std::string> CreatorButtonComponent::SpecificInitComponent(Component* c) {
    UIButtonComponent* progressbar = static_cast<UIButtonComponent*>(c);
   
    
    return progressbar->InitComponent();
}

std::pair<bool, std::string> CreatorButtonComponent::SpecificInitComponentByCopy(Component* c, Component* other) {
    UIButtonComponent* progressbar = static_cast<UIButtonComponent*>(c);
    UIButtonComponent* copia = static_cast<UIButtonComponent*>(other);

     return progressbar->InitComponent();
}
