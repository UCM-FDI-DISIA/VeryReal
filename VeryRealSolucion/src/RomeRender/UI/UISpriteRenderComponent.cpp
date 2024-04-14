#include "UISpriteRenderComponent.h"
#include "Entity.h"
#include "UITransformComponent.h"
#include "Vector2.h"
#include "../RenderManager.h"

#pragma warning(disable : 4251)
#include <OgreRoot.h>
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreEntity.h>
#include <OgreLight.h>
#include <OgreFileSystemLayer.h>
#include <OgreConfigFile.h>
#include <OgreRTShaderSystem.h>
#include <OgreOverlayManager.h>
#include <OgreOverlay.h>
#include <OgreOverlaySystem.h>
#include <OgreTextAreaOverlayElement.h>
#include <OgreOverlayContainer.h>
#include <OgreMaterialManager.h>
#include "OgreTechnique.h"
#include "OgreRenderWindow.h"
#pragma warning(default : 4251)

using namespace VeryReal;

void UiSpriteRenderer::demo() {

#pragma region Sprite


//spritename, materialname y zorder. pos, scale y rot lo coge del transform.
#pragma endregion

#pragma region text


//Ogre::Overlay* overlay = VeryReal::RenderManager::Instance()->GetOverlayManager()->create("Overlaytext");
//Ogre::OverlayContainer* text_container = dynamic_cast<Ogre::OverlayContainer*>(VeryReal::RenderManager::Instance()->GetOverlayManager()->createOverlayElement("Panel", "PanelContainer"));
//Ogre::TextAreaOverlayElement* mTextArea = static_cast<Ogre::TextAreaOverlayElement*>(VeryReal::RenderManager::Instance()->GetOverlayManager()->createOverlayElement("TextArea", "myTextTest"));
//overlay->add2D(text_container);
//overlay->setZOrder(3);
//overlay->setRotate(1);
//mTextArea->setMetricsMode(Ogre::GMM_RELATIVE);
//mTextArea->setFontName("Mario");
//mTextArea->setAlignment(Ogre::TextAreaOverlayElement::Center);
//text_container->addChild(mTextArea);
//
//mTextArea->setPosition(0.4, 0.4);
//mTextArea->setDimensions(1, 1);
//mTextArea->setCharHeight(0.10);
////mTextArea->setColour(Ogre::ColourValue(1,0,0));
////mTextArea->setColour(Ogre::ColourValue(1,0,0));
////mTextArea->setColour(Ogre::ColourValue(1,0,0));
//mTextArea->setColourTop(Ogre::ColourValue(1, 0, 0));
//mTextArea->setColourBottom(Ogre::ColourValue(0, 0, 1));
//mTextArea->setCaption("Ya existe texto perras.");
//overlay->show();

//textname, zorder, fontname, charheight, colorvalue/colorbottom y top, caption. pos, scale y rot lo coge del transform.
#pragma endregion

    //Dimensiones default 1,1. -Posiciones default 0,0.
}

void VeryReal::UiSpriteRenderer::setMaterialName(std::string materialName) {
    material_name = materialName;
    sprite->setMaterialName(materialName);
}

void VeryReal::UiSpriteRenderer::setZOrder(int order) { z_order = order; }

void VeryReal::UiSpriteRenderer::setTransform(Vector2 pos, Vector2 dimension) {
    sprite->setPosition(pos.GetX(), pos.GetY());
    position = pos;
    sprite->setDimensions(dimension.GetX(), dimension.GetY());
    scale = dimension;
}


UiSpriteRenderer::UiSpriteRenderer() { }
UiSpriteRenderer::~UiSpriteRenderer() { }

bool VeryReal::UiSpriteRenderer::InitComponent(std::string name, std::string material, int order) {
    sprite_name = name;
    material_name = material;
    z_order = order;
    overlay_mgr = VeryReal::RenderManager::Instance()->GetOverlayManager();
    overlay = overlay_mgr->create(name + "Overlay");
    sprite = dynamic_cast<Ogre::OverlayContainer*>(overlay_mgr->createOverlayElement("Panel", name + "Panel"));
    transform = GetEntity()->GetComponent<UITransformComponent>();
    setTransform(transform->getPosition(), transform->getSize());
    overlay->add2D(sprite);
    overlay->setZOrder(order);
    sprite->setMaterialName(material);   // Nombre del material del sprit
    overlay->show();
    return true;
}

void UiSpriteRenderer::Update(const double& dt) { setTransform(transform->getPosition(), transform->getSize()); }
