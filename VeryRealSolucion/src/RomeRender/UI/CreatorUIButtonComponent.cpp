#include "CreatorUIButtonComponent.h"
#include "UIButtonComponent.h"
using namespace VeryReal;
Component* CreatorButtonComponent::CreatorSpecificComponent() { return new UIButtonComponent(); }

void CreatorButtonComponent::SpecificInitComponent(Component* c) {
    UIButtonComponent* progressbar = static_cast<UIButtonComponent*>(c);
   
    
    bool b = progressbar->InitComponent();
    if (!b) {
        // Gestion de error
    }
}
