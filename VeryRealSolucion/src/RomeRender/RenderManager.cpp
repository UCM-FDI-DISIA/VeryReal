#include "RenderManager.h"
#include <Ogre.h>
#include <SDL.h>
#include <OgreFileSystem.h>
#include <OgreFileSystemLayer.h>
#include <SDL_syswm.h>
#include <iostream>
#include <Windows.h>
#include <OgreRTShaderSystem.h>
#include "Window.h"
#include <Vector3.h>
#include <OgreVector3.h>
#include "SGTechniqueResolverListener.h"
//mehrender, camara y eso
VeryReal::RenderManager::RenderManager():window_(nullptr),root_(nullptr), scenemanager_(nullptr), rendersystem_(nullptr), viewport_(nullptr), filesystemlayer_(nullptr){
    
}
VeryReal::RenderManager::~RenderManager() {

    if (root_ == nullptr)return;
    //vuelta a la escena por defecto
    root_->destroySceneManager(scenemanager_);
    Ogre::MaterialManager::getSingleton().setActiveScheme(Ogre::MaterialManager::DEFAULT_SCHEME_NAME);

    UnloadShaders();
    delete(window_);
    window_ = nullptr;
    delete root_;
    root_ = nullptr;
    delete filesystemlayer_;
    filesystemlayer_ = nullptr;
    
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
    Ogre::String ogrepath = filesystemlayer_->getConfigFilePath("ogre.cfg");

    root_= new Ogre::Root(pluginsPath, ogrepath);
    if (!root_->restoreConfig())
    {
         root_->showConfigDialog(nullptr);
    }
    //inicializamos root pero sin ventana
    root_->initialise(false);
   
    const Ogre::RenderSystemList renderSystems = root_->getAvailableRenderers();
    rendersystem_ = renderSystems.front();
    root_->setRenderSystem(rendersystem_);

   

    //inicializamos sdl
    if (SDL_WasInit(SDL_INIT_VIDEO))SDL_Init(SDL_INIT_VIDEO);
    SDL_Init(SDL_INIT_EVERYTHING);//mientras no esta todo bien


    scenemanager_ = root_->createSceneManager();
    rendersystem_->_initRenderTargets();//mira esto ni idea que hace


    window_ = new VeryReal::Window(root_, rendersystem_, scenemanager_);
    window_->CreateWindoww();

    //root_->startRendering();

    string sec_name;
    string type_name;
    string arch_name;
    Ogre::String ogrepath2 = filesystemlayer_->getConfigFilePath("resources.cfg");
    Ogre::ConfigFile cf;
    cf.load(ogrepath2);

    Ogre::ConfigFile::SettingsBySection_ seci = cf.getSettingsBySection();
    for (auto i = seci.begin(); i != seci.end(); i++)
    {
        sec_name = i->first;
        Ogre::ConfigFile::SettingsMultiMap settings = i->second;
        Ogre::ConfigFile::SettingsMultiMap::iterator mmi;
        for (mmi = settings.begin(); mmi != settings.end(); ++mmi)
        {
            type_name = mmi->first;
            arch_name = mmi->second;
            Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
                ogrepath2+arch_name, type_name);
        }
    }
   
    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

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
      //  Ogre::MaterialManager::getSingleton().removeListener(materialListener_);
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
Ogre::RenderWindow* VeryReal::RenderManager::GetRenderWindow() {
    return window_->GetOgreWindow();
}
Ogre::SceneManager* VeryReal::RenderManager::SceneManagerOgree() {
    return scenemanager_;
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