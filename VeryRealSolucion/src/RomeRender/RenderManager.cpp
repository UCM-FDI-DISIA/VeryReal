#include "RenderManager.h"
#include <Ogre.h>
#include <SDL.h>
#include <OgreFileSystem.h>
#include <OgreFileSystemLayer.h>
#include <SDL_syswm.h>
#include <iostream>
#include <iostream>
#include <Windows.h>
#include <OgreRTShaderSystem.h>
#include "SGTechniqueResolverListener.h"
#include "Window.h"

//mehrender, camara y eso
VeryReal::RenderManager::RenderManager():window_(nullptr),root_(nullptr), scenemanager_(nullptr), rendersystem_(nullptr), viewport_(nullptr), materialListener_(nullptr), filesystemlayer_(nullptr){

}
VeryReal::RenderManager::~RenderManager() {

}
void VeryReal::RenderManager::InitManager(std::string const& name) {
    appname_ = name;
	filesystemlayer_ = new FileSystemLayer(appname_);
    Ogre::String pluginsPath;
    pluginsPath = filesystemlayer_->getConfigFilePath("plugins.cfg");
    if (!Ogre::FileSystemLayer::fileExists(pluginsPath))
    {
        cerr << "ERROR, no se ha encontrado el archivo  plugins.cfg en la ruta: " << pluginsPath;
    }
    //lo pongo asi y no la rita porque en teoria va a estar al lado del .exe
    root_= new Ogre::Root("plugins.cfg", "ogre.cfg", "Ogre.log");

   
    const Ogre::RenderSystemList renderSystems = root_->getAvailableRenderers();
    rendersystem_ = renderSystems.front();
    root_->setRenderSystem(rendersystem_);

    //inicializamos root pero sin ventana
    root_->initialise(false);

    //inicializamos sdl
    if (SDL_WasInit(SDL_INIT_VIDEO))SDL_Init(SDL_INIT_VIDEO);
    SDL_Init(SDL_INIT_EVERYTHING);//mientras no esta todo bien


    scenemanager_ = root_->createSceneManager();
    rendersystem_->_initRenderTargets();//mira esto ni idea que hace


    window_ = new VeryReal::Window(root_);
    window_->CreateWindoww();


   

 }

void VeryReal::RenderManager::LoadResources() {

    Ogre::ResourceGroupManager::getSingleton().addResourceLocation("./assets", "FileSystem", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, true);
    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

}
void VeryReal::RenderManager::LoadShaders() {
    if (Ogre::RTShader::ShaderGenerator::initialize()) {

        shaderGenerator = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
        shaderGenerator->addSceneManager(scenemanager_);

        materialListener_ = new VeryReal::SGTechniqueResolverListener(shaderGenerator);
        Ogre::MaterialManager::getSingleton().addListener(materialListener_);
    }
}
void VeryReal::RenderManager::UnloadShaders() {
   
    if (materialListener_ != nullptr)
    {
        Ogre::MaterialManager::getSingleton().removeListener(materialListener_);
        delete materialListener_;
        materialListener_ = nullptr;
    }

    // Destroy RTShader system.
    if (shaderGenerator != nullptr)
    {
        Ogre::RTShader::ShaderGenerator::destroy();
        shaderGenerator = nullptr;
    }
}

void VeryReal::RenderManager::Update(const double& dt) {
    root_->renderOneFrame();
 }

Ogre::SceneNode* VeryReal::RenderManager::CreateNode() {
 
    //DA ERROR DE AMBIUEGAD CON VECTOR3 NUESTRO Y VECTOR3 OGRE NO SE
    Ogre::SceneNode* node = scenemanager_->getRootSceneNode()->createChildSceneNode();
    //AQUI VA EL SET POS 
    return node;
}
Ogre::SceneNode* VeryReal::RenderManager::CreateChildSceneNode(Ogre::SceneNode* nod) {
    Ogre::SceneNode* node = scenemanager_->getRootSceneNode()->createChildSceneNode();
    //AQUI VA EL SET POS 
    return node;
}
void VeryReal::RenderManager::DeleteNode(Ogre::SceneNode* nod) {
    

}