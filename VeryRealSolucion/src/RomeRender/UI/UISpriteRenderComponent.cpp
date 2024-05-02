#include "UISpriteRenderComponent.h"
#include "../RenderManager.h"
#include "../conversorvectores.h"
#include "UITransformComponent.h"
//#include <ErrorInformant.h>
#include "Entity.h"

#pragma warning(disable : 4251)
#include <OgreOverlayManager.h>
#include <OgreOverlay.h>
#include <OgreOverlaySystem.h>
#include <OgreTextAreaOverlayElement.h>
#include <OgreOverlayContainer.h>
#include <OgreOverlayElement.h>
#include <Ogre.h>
#pragma warning(default : 4251)

using namespace VeryReal;

void VeryReal::UISpriteRendererComponent::setMaterialName(std::string materialName) {
    material_name = materialName;
    sprite_container->setMaterialName(materialName);
}

void VeryReal::UISpriteRendererComponent::setZOrder(int order) { 
    z_order = order; 
    overlay->setZOrder(order);
}

void VeryReal::UISpriteRendererComponent::setVisibility(bool hide) {
    if (!hide && !overlay->isVisible()) {
        overlay->show(); 
    }
    else if (hide && overlay->isVisible()) {
        overlay->hide();
    }
}

void VeryReal::UISpriteRendererComponent::setSpriteTransform(VeryReal::Vector2 pos, VeryReal::Vector2 sc) {
    sprite_container->setPosition(pos.GetX(), pos.GetY());
    position = pos;
    sprite_container->setDimensions(sc.GetX(), sc.GetY());
    scale = sc;
}
void VeryReal::UISpriteRendererComponent::setScale(VeryReal::Vector2 sc) {
    sprite_container->setDimensions(sc.GetX(), sc.GetY());
    scale = sc;
}
void VeryReal::UISpriteRendererComponent::setPosition(VeryReal::Vector2 pos) {
    sprite_container->setPosition(pos.GetX(), pos.GetY());
    position = pos;
}

UISpriteRendererComponent::UISpriteRendererComponent() 
{

}
UISpriteRendererComponent::~UISpriteRendererComponent() { 
    overlay->remove2D(sprite_container);
    overlay_mgr->destroyOverlayElement(sprite_container);
    overlay_mgr->destroy(overlay);
    sprite_container->cleanupDictionary();
}

bool UISpriteRendererComponent::InitComponent(std::string name, std::string material, int order = 0) { 
    sprite_name = name;
    material_name = material;
    z_order = order;
    overlay_mgr = VeryReal::RenderManager::Instance()->GetOverlayManager();
    overlay = overlay_mgr->create(name + "Overlay");
    sprite_container = dynamic_cast<Ogre::OverlayContainer*>(overlay_mgr->createOverlayElement("Panel", name + "Panel"));
    transform = GetEntity()->GetComponent<UITransformComponent>();

    //if (!transform) {
    //    ErrorInf().showErrorMessageBox("UISpriteRendererComponent error", "An entity doesn't have transform component", EI_ERROR);
    //    //sceneManager().quit();
    //    return false;
    //}

    setSpriteTransform(transform->getPosition(), transform->getScale());
    overlay->add2D(sprite_container);
    overlay->setZOrder(order);
    sprite_container->setMaterialName(material);   // Nombre del material del sprit
    bool que = transform->isHidden();
    setVisibility(que);
    return true;
}
void UISpriteRendererComponent::Update(const double& dt) {
    setSpriteTransform(transform->getPosition(), transform->getScale());
    bool que = transform->isHidden();
    setVisibility(que);
}
