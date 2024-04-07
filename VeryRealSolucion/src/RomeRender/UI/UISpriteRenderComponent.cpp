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
#include <OgreOverlayContainer.h>
#include <OgreMaterialManager.h>
#include "OgreTechnique.h"
#include "OgreRenderWindow.h"
#pragma warning(default : 4251)

using namespace VeryReal;

void UiSpriteRenderer::demo() { 

	VeryReal::RenderManager::Instance()->InitManager("app");
    Ogre::OverlaySystem* overlaySystem = new Ogre::OverlaySystem();
    Ogre::OverlayManager& overlayManager = Ogre::OverlayManager::getSingleton();
    Ogre::Overlay* overlay = overlayManager.create("OverlaySprite");
    Ogre::SceneManager* mgr = VeryReal::RenderManager::Instance()->SceneManagerOgree();
    Ogre::Camera* camera = mgr->createCamera("CamaraPrincipal");
    Ogre::OverlayContainer* container = dynamic_cast<Ogre::OverlayContainer*>(overlayManager.createOverlayElement("Panel", "PanelContainer"));
    container->setPosition(0, 0);
    container->setDimensions(1, 1);
    overlay->add2D(container);
    Ogre::OverlayElement* sprite = overlayManager.createOverlayElement("Panel", "Sprite");
    sprite->setDimensions(100, 100);             // Tamaño del sprite
    sprite->setPosition(100, 100);               // Posición del sprite
    sprite->setMaterialName("MaterialSprite");   // Nombre del material del sprite
    container->addChild(sprite);
    Ogre::MaterialPtr material =
        Ogre::MaterialManager::getSingleton().create("MaterialSprite", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
    material->getTechnique(0)->getPass(0)->createTextureUnitState("prueba.png");
    Ogre::Viewport* viewport = VeryReal::RenderManager::Instance()->GetRenderWindow()->addViewport(camera);
    viewport->setBackgroundColour(Ogre::ColourValue(0.0, 0.0, 0.0));
    camera->setAspectRatio(Ogre::Real(viewport->getActualWidth()) / Ogre::Real(viewport->getActualHeight()));
    overlay->show();
    VeryReal::RenderManager::Instance()->GetRenderRoot()->renderOneFrame();
}

UiSpriteRenderer::UiSpriteRenderer() 
{

}
UiSpriteRenderer::~UiSpriteRenderer() { }

bool UiSpriteRenderer::InitComponent() { return false; }
void UiSpriteRenderer::Update(const double& dt) { }
