#include "UISpriteRenderComponent.h"
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
    #pragma endregion


}

UiSpriteRenderer::UiSpriteRenderer() 
{

}
UiSpriteRenderer::~UiSpriteRenderer() { }

bool UiSpriteRenderer::InitComponent(std::string name, std::string material, int order) { return false; }
void UiSpriteRenderer::Update(const double& dt) { }
