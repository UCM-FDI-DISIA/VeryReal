#include "UITransformComponent.h"


using namespace VeryReal;
using namespace std;

UITransformComponent::UITransformComponent() { 

}
bool UITransformComponent::InitComponent(VeryReal::Vector2 pos, VeryReal::Vector2 scale, bool hide, bool interact) {
    position = pos;
    size = scale;
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

