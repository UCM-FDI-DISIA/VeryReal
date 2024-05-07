#pragma once
#pragma warning(disable : 4251)
#include <Ogre.h>
#include <OgreFileSystem.h>
#include <OgreFileSystemLayer.h>
#include <OgreOverlayManager.h>
#include <OgreOverlaySystem.h>
#include <OgreRTShaderSystem.h>
#pragma warning(disable : 4251)

#include "RenderManager.h"
#include <SDL.h>
#include <SDL_syswm.h>
#include <iostream>
#include <Windows.h>
#include "Window.h"
#include "SGTechniqueResolverListener.h"
#include "conversorvectores.h"
#include "OgreEntity.h"
//mehrender, camara y eso
VeryReal::RenderManager::~RenderManager() {


    if (root == nullptr) {
#ifdef DEBUG_MODE
        cerr << DEBUG_ROOT_ERROR;
#endif
        return;
    }

    if (scene_manager != nullptr) {

        root->destroySceneManager(scene_manager);
    }
    //// Limpiar todos los materiales
    Ogre::MaterialManager::getSingleton().removeAll();

    //// Limpiar todas las texturas
    Ogre::TextureManager::getSingleton().removeAll();

    //// Limpiar el MeshManager
    Ogre::MeshManager::getSingleton().removeAll();

    delete (window);

    window = nullptr;
    //delete filesystem_layer;
    //filesystem_layer = nullptr;
    delete (overlay_system);
    root->shutdown();
    root->unloadPlugin("plugins.cfg");
    delete (root);
    delete filesystem_layer;
    filesystem_layer = nullptr;
    //  delete window->GetOgreWindow();
    //  mOgreWindow = nullptr;


    root = nullptr;

}
std::pair<bool, std::string> VeryReal::RenderManager::InitManager(std::string const& name) 
{
    window = nullptr;
    root = nullptr;
    scene_manager = nullptr;
    render_system = nullptr;
    viewport=nullptr;
    filesystem_layer = nullptr;
    appname = name;
    filesystem_layer = new Ogre::FileSystemLayer(appname);
    Ogre::String pluginsPath;
    pluginsPath = filesystem_layer->getConfigFilePath("plugins.cfg");
    if (!Ogre::FileSystemLayer::fileExists(pluginsPath)) {
        return {false, "The file to get the plugins from was not found"};
    }
    //lo pongo asi y no la rita porque en teoria va a estar al lado del .exe
    Ogre::String ogrepath = filesystem_layer->getConfigFilePath("ogre.cfg");
    if (!Ogre::FileSystemLayer::fileExists(ogrepath)) {
        return {false, "The file to get the Ogre config from was not found"};
    }
    root = new Ogre::Root(pluginsPath, ogrepath);
    if (!root->restoreConfig()) {
        root->showConfigDialog(nullptr);
    }

    overlay_system = new Ogre::OverlaySystem();
    overlay_manager = Ogre::OverlayManager::getSingletonPtr();
    //inicializamos root pero sin ventana
    root->initialise(false);

    const Ogre::RenderSystemList renderSystems = root->getAvailableRenderers();
    render_system = renderSystems.front();
    root->setRenderSystem(render_system);


    //inicializamos sdl
    if (!SDL_WasInit(SDL_INIT_VIDEO)) SDL_Init(SDL_INIT_VIDEO);

    scene_manager = root->createSceneManager();
    render_system->_initRenderTargets();   //mira esto ni idea que hace


    window = new VeryReal::Window();
    if (window->Init(root, render_system, scene_manager)) {
        auto createWindow = window->CreateWindoww();
        if (!createWindow.first) return createWindow;
    }
    else {
        return {false, "The window couldn't init"};
    }


    //root->startRendering();

    std::string sec_name;
    std::string type_name;
    std::string arch_name;
    Ogre::String ogrepath2 = filesystem_layer->getConfigFilePath("resources.cfg");
    if (!Ogre::FileSystemLayer::fileExists(ogrepath2)) {
        return {false, "The path to get the resources wasn't found"};
    }
    Ogre::ConfigFile cf;    
    cf.load(ogrepath2);

    Ogre::ConfigFile::SettingsBySection_ seci = cf.getSettingsBySection();
    for (auto i = seci.begin(); i != seci.end(); i++) {
        sec_name = i->first;
        Ogre::ConfigFile::SettingsMultiMap settings = i->second;
        Ogre::ConfigFile::SettingsMultiMap::iterator mmi;
        for (mmi = settings.begin(); mmi != settings.end(); ++mmi) {
            type_name = mmi->first;
            arch_name = mmi->second;
            Ogre::ResourceGroupManager::getSingleton().addResourceLocation(ogrepath2 + arch_name, type_name);
        }
    }

   
    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
    SceneManagerOgree()->addRenderQueueListener(overlay_system);
    return {true, "Render sucesfully initialized"};
}


void VeryReal::RenderManager::LoadResources() {

    Ogre::ResourceGroupManager::getSingleton().addResourceLocation("./assets", "FileSystem", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
                                                                   true);
    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}

Ogre::RenderWindow* VeryReal::RenderManager::GetRenderWindow() { return window->GetOgreWindow(); }
Ogre::Root* VeryReal::RenderManager::GetRenderRoot() { return root; }
Ogre::SceneManager* VeryReal::RenderManager::SceneManagerOgree() { return scene_manager; }
Ogre::OverlayManager* VeryReal::RenderManager::GetOverlayManager() { return overlay_manager; }
Ogre::OverlaySystem* VeryReal::RenderManager::GetOverlaySystem() { return overlay_system; }
VeryReal::Window* VeryReal::RenderManager::GetVRWindow() { return window; }
void VeryReal::RenderManager::Update(const double& dt) { root->renderOneFrame(); }


Ogre::SceneNode* VeryReal::RenderManager::CreateNode(VeryReal::Vector3 vec) {

    //DA ERROR DE AMBIUEGAD CON VECTOR3 NUESTRO Y VECTOR3 OGRE NO SE
    Ogre::SceneNode* node = scene_manager->getRootSceneNode()->createChildSceneNode();
    //AQUI VA EL SET POS
    node->setPosition(VR2OgreV3(vec));
    return node;
}
Ogre::SceneNode* VeryReal::RenderManager::CreateChildSceneNode(Ogre::SceneNode* nod, VeryReal::Vector3 vec) {
    Ogre::SceneNode* node = scene_manager->getRootSceneNode()->createChildSceneNode();
    //AQUI VA EL SET POS
    node->setPosition(VR2OgreV3(vec));
    return node;
}
void VeryReal::RenderManager::DeleteNode(Ogre::SceneNode* nod) {

    scene_manager->destroySceneNode(nod);

    // delete(nod);
}
void VeryReal::RenderManager::DeleteEntity(Ogre::Entity* nod) {
    //Ogre::MeshManager::getSingleton().remove(nod->getMesh()->getName());
}


Ogre::ManualObject* VeryReal::RenderManager::createManualObject(Ogre::SceneNode* node) {
    Ogre::ManualObject* newManualObject = scene_manager->createManualObject();
    node->attachObject(newManualObject);
    return newManualObject;
}

Ogre::SceneManager* VeryReal::RenderManager::getSceneManager() { return scene_manager; }

void VeryReal::RenderManager::destroyManualObject(Ogre::ManualObject* const object) { scene_manager->destroyManualObject(object); }
