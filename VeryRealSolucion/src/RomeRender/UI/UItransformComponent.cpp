
#include "UItransformComponent.h"
using namespace VeryReal;
using namespace std;

UITransformComponent::UITransformComponent() { 
    hidden = interactive = false;
}
bool UITransformComponent::InitComponent() {
    
    return true;
}
UITransformComponent::~UITransformComponent() { }
void UITransformComponent::Update(const double& dt) { }
void UITransformComponent::showElement() { hidden = false; }
void UITransformComponent::hideElement() { hidden = true; }
VeryReal::Vector2 UITransformComponent::getPosition() { return position; }
void UITransformComponent::setPosition(VeryReal::Vector2 pos) { 
    position = pos; }
VeryReal::Vector2 UITransformComponent::getSize() { return size; }
void UITransformComponent::setSize(VeryReal::Vector2 siz) { 
    size = siz;
}

void UITransformComponent::setInteractive(bool inter) { 
    interactive = inter; }

bool UITransformComponent::isHidden() {
    return hidden;
}

