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
VeryReal::RenderManager::RenderManager():window(nullptr),root(nullptr), scene_manager(nullptr), render_system(nullptr), viewport(nullptr), filesystem_layer(nullptr){
    
}
VeryReal::RenderManager::~RenderManager() {

    if (root == nullptr) { std::cerr << "RenderManager no ha sido inicializado\n"; return; }
    //vuelta a la escena por defecto
    root->destroySceneManager(scene_manager);
    Ogre::MaterialManager::getSingleton().setActiveScheme(Ogre::MaterialManager::DEFAULT_SCHEME_NAME);

    UnloadShaders();
    delete(window);
    window = nullptr;
    delete root;
    root = nullptr;
    delete filesystem_layer;
    filesystem_layer = nullptr;
    
}
void VeryReal::RenderManager::InitManager(std::string const& name) {
    appname = name;
	filesystem_layer = new Ogre::FileSystemLayer(appname);
    Ogre::String pluginsPath;
    pluginsPath = filesystem_layer->getConfigFilePath("plugins.cfg");
    if (!Ogre::FileSystemLayer::fileExists(pluginsPath))
    {
        std::cerr << "ERROR, no se ha encontrado el archivo  plugins.cfg en la ruta: " << pluginsPath;
    }
    //lo pongo asi y no la rita porque en teoria va a estar al lado del .exe
    Ogre::String ogrepath = filesystem_layer->getConfigFilePath("ogre.cfg");

    root= new Ogre::Root(pluginsPath, ogrepath);
    if (!root->restoreConfig())
    {
         root->showConfigDialog(nullptr);
    }
    //inicializamos root pero sin ventana
    root->initialise(false);
   
    const Ogre::RenderSystemList renderSystems = root->getAvailableRenderers();
    render_system = renderSystems.front();
    root->setRenderSystem(render_system);

   

    //inicializamos sdl
    if (SDL_WasInit(SDL_INIT_VIDEO))SDL_Init(SDL_INIT_VIDEO);
    SDL_Init(SDL_INIT_EVERYTHING);//mientras no esta todo bien


    scene_manager = root->createSceneManager();
    render_system->_initRenderTargets();//mira esto ni idea que hace


    window = new VeryReal::Window(root, render_system, scene_manager);
    window->CreateWindoww();

    //root->startRendering();

    std::string sec_name;
    std::string type_name;
    std::string arch_name;
    Ogre::String ogrepath2 = filesystem_layer->getConfigFilePath("resources.cfg");
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

        shader_generator = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
        shader_generator->addSceneManager(scene_manager);

        material_listener = new VeryReal::SGTechniqueResolverListener(shader_generator);
        Ogre::MaterialManager::getSingleton().addListener(material_listener);
    }
}
void VeryReal::RenderManager::UnloadShaders() {
   
    if (material_listener != nullptr)
    {
      //  Ogre::MaterialManager::getSingleton().removeListener(material_listener);
        delete material_listener;
        material_listener = nullptr;
    }

    // Destroy RTShader system.
    if (shader_generator!= nullptr)
    {
       
        Ogre::RTShader::ShaderGenerator::destroy();
        shader_generator = nullptr;
    }
}
Ogre::RenderWindow* VeryReal::RenderManager::GetRenderWindow() {
    return window->GetOgreWindow();
}
Ogre::SceneManager* VeryReal::RenderManager::SceneManagerOgree() {
    return scene_manager;
}
void VeryReal::RenderManager::Update(const double& dt) {
    root->renderOneFrame();
   
 }

Ogre::SceneNode* VeryReal::RenderManager::CreateNode(VeryReal::Vector3 vec) {
 
    //DA ERROR DE AMBIUEGAD CON VECTOR3 NUESTRO Y VECTOR3 OGRE NO SE
    Ogre::SceneNode* node = scene_manager->getRootSceneNode()->createChildSceneNode();
    //AQUI VA EL SET POS 
    node->setPosition({ vec.GetX(),vec.GetY(),vec.GetZ() });
    return node;
}
Ogre::SceneNode* VeryReal::RenderManager::CreateChildSceneNode(Ogre::SceneNode* nod, VeryReal::Vector3 vec) {
    Ogre::SceneNode* node = scene_manager->getRootSceneNode()->createChildSceneNode();
    //AQUI VA EL SET POS 
    node->setPosition({ vec.GetX(),vec.GetY(),vec.GetZ() });
    return node;
}
void VeryReal::RenderManager::DeleteNode(Ogre::SceneNode* nod) {
    
    scene_manager->destroySceneNode(nod);

   // delete(nod);
}