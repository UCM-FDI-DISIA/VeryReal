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

void CreatorButtonComponent::SpecificInitComponentByCopy(Component* c, Component* other) {
    UIButtonComponent* progressbar = static_cast<UIButtonComponent*>(c);
    UIButtonComponent* copia = static_cast<UIButtonComponent*>(other);

    // Pillar las variables de la copia si se necesitasen
    bool b = progressbar->InitComponent();
    if (!b) {
        // Gestion de error
    }
}
