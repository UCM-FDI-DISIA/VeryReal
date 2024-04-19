#include "UITransformComponent.h"


using namespace VeryReal;
using namespace std;

UITransformComponent::UITransformComponent() { 

}
bool UITransformComponent::InitComponent(VeryReal::Vector2 pos, VeryReal::Vector2 sc, bool hide, bool interact) {
    position = pos;
    scale = sc;
    hidden = hide;
    return true;
}
UITransformComponent::~UITransformComponent() { }
void UITransformComponent::Update(const double& dt) { }
void UITransformComponent::showElement() { hidden = false; }
void UITransformComponent::hideElement() { hidden = true; }
VeryReal::Vector2 UITransformComponent::getPosition() { return position; }
void UITransformComponent::setPosition(VeryReal::Vector2 pos) { 
    position = pos; }

VeryReal::Vector2 VeryReal::UITransformComponent::getScale() { 
    return scale; 
}

void VeryReal::UITransformComponent::setScale(VeryReal::Vector2 sc) {
    scale = sc;
}

void UITransformComponent::setInteractive(bool inter) { 
    interactive = inter; }

bool UITransformComponent::isHidden() {
    return hidden;
}

