#include "UITextComponent.h"
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
#include <Ogre.h>
#pragma warning(default : 4251)

using namespace VeryReal;

VeryReal::UITextComponent::UITextComponent() { }

VeryReal::UITextComponent::~UITextComponent() {
    overlay->remove2D(text_container);
    text_container->removeChild(text_area->getName());
    overlay_mgr->destroyOverlayElement(text_area);
    overlay_mgr->destroyOverlayElement(text_container);
    overlay_mgr->destroy(overlay);
    text_container->cleanupDictionary();
    text_area->cleanupDictionary();
}

bool VeryReal::UITextComponent::InitComponent(std::string name, std::string font, int order, float height, VeryReal::Vector3 clr,
                                              std::string caption) {
    normal_or_topbottom = true;
    text_name = name;
    font_name = font;
    z_order = order;
    char_height = height;
    color = clr;
    text_caption = caption;
    overlay_mgr = VeryReal::RenderManager::Instance()->GetOverlayManager();
    overlay = VeryReal::RenderManager::Instance()->GetOverlayManager()->create(name + "Overlay");
    text_container = dynamic_cast<Ogre::OverlayContainer*>(overlay_mgr->createOverlayElement("Panel", name + "Panel"));
    text_area = static_cast<Ogre::TextAreaOverlayElement*>(overlay_mgr->createOverlayElement("TextArea", name + "Text"));
    transform = GetEntity()->GetComponent<UITransformComponent>();

    //if (!transform) {
    //    ErrorInf().showErrorMessageBox("UISpriteRendererComponent error", "An entity doesn't have transform component", EI_ERROR);
    //    //sceneManager().quit();
    //    return false;
    //}

    setTextTransform(transform->getPosition(), transform->getScale(), transform->isHidden());
    overlay->add2D(text_container);
    overlay->setZOrder(order);
    text_area->setMetricsMode(Ogre::GMM_RELATIVE);
    text_area->setFontName(font_name);
    text_area->setAlignment(Ogre::TextAreaOverlayElement::Center);
    text_container->addChild(text_area);
    text_area->setCharHeight(height);
    setColor(clr);
    text_area->setCaption(caption);
    overlay->show();

    return true;
}

bool VeryReal::UITextComponent::InitComponent(std::string name, std::string font, int order, float height, VeryReal::Vector3 bottomcolor,
                                              VeryReal::Vector3 topcolor, std::string caption) {
    normal_or_topbottom = false;
    text_name = name;
    font_name = font;
    z_order = order;
    char_height = height;
    color_bottom = bottomcolor;
    color_top = topcolor;
    text_caption = caption;
    overlay_mgr = VeryReal::RenderManager::Instance()->GetOverlayManager();
    overlay = overlay_mgr->create(name + "Overlay");
    text_container = dynamic_cast<Ogre::OverlayContainer*>(overlay_mgr->createOverlayElement("Panel", name + "Panel"));
    text_area = static_cast<Ogre::TextAreaOverlayElement*>(overlay_mgr->createOverlayElement("TextArea", name + "Text"));
    transform = GetEntity()->GetComponent<UITransformComponent>();

    //if (!transform) {
    //    ErrorInf().showErrorMessageBox("UISpriteRendererComponent error", "An entity doesn't have transform component", EI_ERROR);
    //    //sceneManager().quit();
    //    return false;
    //}

    setTextTransform(transform->getPosition(), transform->getScale(), transform->isHidden());
    overlay->add2D(text_container);
    overlay->setZOrder(order);
    text_area->setMetricsMode(Ogre::GMM_RELATIVE);
    text_area->setFontName(font_name);
    text_area->setAlignment(Ogre::TextAreaOverlayElement::Center);
    text_container->addChild(text_area);
    text_area->setCharHeight(height);
    setTopColor(topcolor);
    setBottomColor(bottomcolor);
    text_area->setCaption(caption);
    overlay->show();

    return true;
}

void VeryReal::UITextComponent::Update(const double& dt) { 
    setTextTransform(transform->getPosition(), transform->getScale(), transform->isHidden()); 
}

void VeryReal::UITextComponent::setFontName(std::string fontName) { 
    font_name = fontName;
    text_area->setMaterialName(fontName);
}

void VeryReal::UITextComponent::setZOrder(int order) { 
    z_order = order; 
    overlay->setZOrder(order);
}

void VeryReal::UITextComponent::setCaption(std::string newCap) {
    text_caption = newCap;
    text_area->setCaption(newCap);
}

void VeryReal::UITextComponent::setCharHeight(float height) { 
    char_height = height;
    text_area->setCharHeight(height);
}

void VeryReal::UITextComponent::setColor(VeryReal::Vector3 newColor) {
    color = newColor;
    text_area->setColour(Ogre::ColourValue(newColor.GetX(), newColor.GetY(), newColor.GetZ()));
}

void VeryReal::UITextComponent::setTopColor(VeryReal::Vector3 newColor) { 
    color_top = newColor;
    text_area->setColourTop(Ogre::ColourValue(newColor.GetX(), newColor.GetY(), newColor.GetZ()));
}

void VeryReal::UITextComponent::setBottomColor(VeryReal::Vector3 newColor) {
    color_bottom = newColor;
    text_area->setColourBottom(Ogre::ColourValue(newColor.GetX(), newColor.GetY(), newColor.GetZ()));
}

void VeryReal::UITextComponent::setTextTransform(VeryReal::Vector2 pos, VeryReal::Vector2 sc, bool show) {
    text_area->setPosition(pos.GetX(), pos.GetY());
    position = pos;
    text_area->setDimensions(sc.GetX(), sc.GetY());
    scale = sc;
    /*if (show) {
        overlay->show();
    }
    else {
        overlay->hide();
    }*/
}
