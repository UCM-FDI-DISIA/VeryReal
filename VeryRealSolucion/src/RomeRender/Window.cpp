#include "Window.h"
#include <Ogre.h>
#include <SDL.h>
#include <OgreFileSystem.h>
#include <OgreFileSystemLayer.h>
#include <SDL_syswm.h>
#undef main   
#include <iostream>
using namespace VeryReal;
using namespace Ogre;

Window::Window(Ogre::Root* root):scene_manager(nullptr),render_system(nullptr),ogre_window(nullptr),sdl_window(nullptr) {
    name = "VeryReall";
    this->root = root;
}

Window::~Window() {
    if (ogre_window != nullptr) root->destroyRenderTarget(ogre_window);
    if (sdl_window != nullptr) {
        SDL_DestroyWindow(sdl_window);
        SDL_VideoQuit();
    }
    ogre_window = nullptr;
    sdl_window = nullptr;
}

void Window::Init() {
    // creamos un nuevo filesystem layer
    file_system_layer = new Ogre::FileSystemLayer("VeryReal"); 
    Ogre::String plugins_path;
    //asignamos la ruta para las configuraciones de la pantalla
    ruta_configuracion = file_system_layer->getConfigFilePath("plugins.cfg");
 
    file_system_layer->setHomePath(ruta_configuracion);
    if(root==nullptr)root = new Ogre::Root(ruta_configuracion+ "\\..\\", "", file_system_layer->getWritablePath("ogre.log"));//esto no va asi vale es solo temp
    
    //obtenermos el render system de tipo GL (los datos se descargan en el .bat)
    //como esto no nos va lo cargamos a mano
    root->loadPlugin("RenderSystem_GL");
    Ogre::RenderSystem* renderSystem = root->getRenderSystemByName("GL Rendering Subsystem");
    const Ogre::RenderSystemList renderSystems = root->getAvailableRenderers();
    render_system = renderSystems.front();
    root->setRenderSystem(render_system);
   //inicializamos root pero sin ventana
    root->initialise(false);

    //inicializamos sdl
    if(SDL_WasInit(SDL_INIT_VIDEO))SDL_Init(SDL_INIT_VIDEO);
    SDL_Init(SDL_INIT_EVERYTHING);//mientras no esta todo bien


    Ogre::NameValuePairList miscParams;
    Ogre::ConfigOptionMap ropts = render_system->getConfigOptions();
    //cogemos un modo de configuracion (solo ese modo tiene alto y ancho?)
    std::istringstream mode(ropts["Video Mode"].currentValue);
    Ogre::String token;
    mode >> window_width;    
    mode >> token;         
    mode >> window_height;   
    miscParams["FSAA"] = ropts["FSAA"].currentValue;
    miscParams["gamma"] = ropts["sRGB Gamma Conversion"].currentValue;
    miscParams["vsync"] = ropts["VSync"].currentValue;
    Uint32 flags = SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI;
    //si es pantalla completa se pone entero (porque no tiene los datos puestos?)

    if (ropts["Full Screen"].currentValue == "Yes") flags = SDL_WINDOW_FULLSCREEN | SDL_WINDOW_ALLOW_HIGHDPI;
    //cramos una ventana de SDL
    sdl_window = SDL_CreateWindow(
        name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, window_width, window_height, flags);

    SDL_SysWMinfo wmInfo;
    SDL_VERSION(&wmInfo.version);
    SDL_GetWindowWMInfo(sdl_window, &wmInfo);//obtenemos la info de la ventana que acabamos de cerar con sdl para ahora pasarsela a pgre como ventana externa

    miscParams["externalWindowHandle"] = Ogre::StringConverter::toString(size_t(wmInfo.info.win.window));
    //pasamos los valores a una ventana de ogre a partir de la ventana de sdl creada
    ogre_window = root->createRenderWindow(name, window_width, window_height, false, &miscParams);
  
   
}
void  Window::demo(){

    //ESTO NO VA AQUI ES SOLO PARA LA DEMO
    scene_manager = root->createSceneManager();
    render_system->_initRenderTargets();
    //asignamos la 
    string ruta = ruta_configuracion + "\\..\\Assets";
    Ogre::ResourceGroupManager::getSingleton().addResourceLocation(ruta, "FileSystem");
    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
    //luz principal
    Ogre::Light* light = scene_manager->createLight("LuzPrincipal");
    Ogre::SceneNode* lightNode = scene_manager->getRootSceneNode()->createChildSceneNode();
    lightNode->setPosition(-10, 0, 0);
    lightNode->attachObject(light);

    //camara
    Ogre::SceneNode* camNode = scene_manager->getRootSceneNode()->createChildSceneNode(); //nodo  de la camara
    camNode->lookAt(Ogre::Vector3(0, 0, -1), Ogre::Node::TS_PARENT);
    camNode->setPosition(0, 0, 30);
    Ogre::Camera* cam = scene_manager->createCamera("Camara"); // objetoi camara en si 
    cam->setNearClipDistance(1); //queremos que serenderice lo mas cerca posible desde la camara
    camNode->attachObject(cam);
    Ogre::Viewport* vp = ogre_window->addViewport(cam);


    //cambio de color de fondo
    vp->setBackgroundColour(Ogre::ColourValue(0.1, 0.2, 0.3));

    //cargamos sinbad SOLO SE PUEDEN CARGAR .MESH
    Ogre::Entity* ent = scene_manager->createEntity("Sinbad.mesh");
    Ogre::SceneNode* node = scene_manager->getRootSceneNode()->createChildSceneNode();
    node->attachObject(ent);
    //BUCLE PARA QUE NO SE CIERRE LA VENANA SE TIENE QUE QUITAR
    root->startRendering();
    while (true) {
        root->renderOneFrame();
    }
}

SDL_Window* Window::CreateWindoww() {
    // creamos un nuevo filesystem layer
    file_system_layer = new Ogre::FileSystemLayer("VeryReal");
    Ogre::String plugins_path;
    //asignamos la ruta para las configuraciones de la pantalla
    ruta_configuracion = file_system_layer->getConfigFilePath("plugins.cfg");

    file_system_layer->setHomePath(ruta_configuracion);
    if (root == nullptr)root = new Ogre::Root(ruta_configuracion + "\\..\\", "", file_system_layer->getWritablePath("ogre.log"));//esto no va asi vale es solo temp

    //obtenermos el render system de tipo GL (los datos se descargan en el .bat)
    //como esto no nos va lo cargamos a mano
    root->loadPlugin("RenderSystem_GL");
    Ogre::RenderSystem* renderSystem = root->getRenderSystemByName("GL Rendering Subsystem");
    const Ogre::RenderSystemList renderSystems = root->getAvailableRenderers();
    render_system = renderSystems.front();
    root->setRenderSystem(render_system);
    //inicializamos root pero sin ventana
    root->initialise(false);

    //inicializamos sdl
    if (SDL_WasInit(SDL_INIT_VIDEO))SDL_Init(SDL_INIT_VIDEO);
    SDL_Init(SDL_INIT_EVERYTHING);//mientras no esta todo bien


    Ogre::NameValuePairList miscParams;
    Ogre::ConfigOptionMap ropts = render_system->getConfigOptions();
    //cogemos un modo de configuracion (solo ese modo tiene alto y ancho?)
    std::istringstream mode(ropts["Video Mode"].currentValue);
    Ogre::String token;
    mode >> window_width;
    mode >> token;
    mode >> window_height;
    miscParams["FSAA"] = ropts["FSAA"].currentValue;
    miscParams["gamma"] = ropts["sRGB Gamma Conversion"].currentValue;
    miscParams["vsync"] = ropts["VSync"].currentValue;
    Uint32 flags = SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI;
    //si es pantalla completa se pone entero (porque no tiene los datos puestos?)

    if (ropts["Full Screen"].currentValue == "Yes") flags = SDL_WINDOW_FULLSCREEN | SDL_WINDOW_ALLOW_HIGHDPI;
    //cramos una ventana de SDL
    sdl_window = SDL_CreateWindow(
        name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, window_width, window_height, flags);

    SDL_SysWMinfo wmInfo;
    SDL_VERSION(&wmInfo.version);
    SDL_GetWindowWMInfo(sdl_window, &wmInfo);//obtenemos la info de la ventana que acabamos de cerar con sdl para ahora pasarsela a pgre como ventana externa

    miscParams["externalWindowHandle"] = Ogre::StringConverter::toString(size_t(wmInfo.info.win.window));
    //pasamos los valores a una ventana de ogre a partir de la ventana de sdl creada
    ogre_window = root->createRenderWindow(name, window_width, window_height, false, &miscParams);
    return sdl_window;

}

void Window::Update() {
    if (sdl_window != nullptr && ogre_window != nullptr) {

        //aqui van las cosas del input de la ventana tipo si se cierra y eso
    }
}

SDL_Window* Window::GetSDLWindow() {
    return sdl_window;
}
Ogre::RenderWindow* Window::GetOgreWindow() {
    return ogre_window;
}