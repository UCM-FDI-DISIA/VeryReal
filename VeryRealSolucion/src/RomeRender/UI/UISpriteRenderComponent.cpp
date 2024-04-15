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
#include <Ogre.h>
#pragma warning(default : 4251)

using namespace VeryReal;

void VeryReal::UiSpriteRenderer::setMaterialName(std::string materialName) {
    material_name = materialName;
    sprite->setMaterialName(materialName);
}

void VeryReal::UiSpriteRenderer::setZOrder(int order) { 
    z_order = order; 
    overlay->setZOrder(order);
}

void VeryReal::UiSpriteRenderer::setSpriteTransform(VeryReal::Vector2 pos, VeryReal::Vector2 sc, bool show) {
    sprite->setPosition(pos.GetX(), pos.GetY());
    position = pos;
    sprite->setDimensions(sc.GetX(), sc.GetY());
    scale = sc;
    /*if (show) {
        overlay->show();
    }
    else {
        overlay->hide();
    }*/
}

void UiSpriteRenderer::demo() { 

    #pragma region Sprite
    //Ogre::Overlay* overlay = overlayManager->create("OverlaySprite");
    //Ogre::SceneManager* mgr = VeryReal::RenderManager::Instance()->SceneManagerOgree();
    //Ogre::OverlayContainer* sprite = dynamic_cast<Ogre::OverlayContainer*>(overlayManager->createOverlayElement("Panel", "PanelContainer"));
    //sprite->setPosition(0, 0);
    //sprite->setDimensions(1, 1);
    //overlay->add2D(sprite);
    //overlay->setZOrder(3);
    //sprite->setMaterialName("UI/test");   // Nombre del material del sprit
    //overlay->show();
    #pragma endregion

    #pragma region text


    Ogre::Overlay* overlay = VeryReal::RenderManager::Instance()->GetOverlayManager()->create("Overlaytext");
    Ogre::OverlayContainer* text_container = dynamic_cast<Ogre::OverlayContainer*>(VeryReal::RenderManager::Instance()->GetOverlayManager()->createOverlayElement("Panel", "PanelContainer"));
    Ogre::TextAreaOverlayElement* mTextArea = static_cast<Ogre::TextAreaOverlayElement*>(VeryReal::RenderManager::Instance()->GetOverlayManager()->createOverlayElement("TextArea", "myTextTest"));
    overlay->add2D(text_container);
    overlay->setZOrder(3);
    mTextArea->setMetricsMode(Ogre::GMM_RELATIVE);
    mTextArea->setFontName("Mario");
    mTextArea->setAlignment(Ogre::TextAreaOverlayElement::Center);
    text_container->addChild(mTextArea);
    
    mTextArea->setPosition(0.4, 0.4);
    mTextArea->setDimensions(1, 1);
    mTextArea->setCharHeight(0.10);
    //mTextArea->setColour(Ogre::ColourValue(1,0,0));
    //mTextArea->setColour(Ogre::ColourValue(1,0,0));
    //mTextArea->setColour(Ogre::ColourValue(1,0,0));
    mTextArea->setColourTop(Ogre::ColourValue(1, 0, 0));
    mTextArea->setColourBottom(Ogre::ColourValue(0, 0, 1));
    mTextArea->setCaption("Ya existe texto perras.");
    overlay->show();
    //textname, zorder, fontname, charheight, colorvalue/colorbottom y top, caption. pos, scale y rot lo coge del transform.

    #pragma endregion


}

UiSpriteRenderer::UiSpriteRenderer() 
{

}
UiSpriteRenderer::~UiSpriteRenderer() { }

bool UiSpriteRenderer::InitComponent(std::string name, std::string material, int order = 0) { 
    sprite_name = name;
    material_name = material;
    z_order = order;
    overlay_mgr = VeryReal::RenderManager::Instance()->GetOverlayManager();
    overlay = overlay_mgr->create(name + "Overlay");
    sprite = dynamic_cast<Ogre::OverlayContainer*>(overlay_mgr->createOverlayElement("Panel", name + "Panel"));
    transform = GetEntity()->GetComponent<UITransformComponent>();

    //if (!transform) {
    //    ErrorInf().showErrorMessageBox("UiSpriteRenderer error", "An entity doesn't have transform component", EI_ERROR);
    //    //sceneManager().quit();
    //    return false;
    //}

    setSpriteTransform(transform->getPosition(), transform->getScale());
    overlay->add2D(sprite);
    overlay->setZOrder(order);
    sprite->setMaterialName(material);   // Nombre del material del sprit
    overlay->show();
    return true;
}
void UiSpriteRenderer::Update(const double& dt) {
    setSpriteTransform(transform->getPosition(), transform->getScale(), transform->isHidden());
}
