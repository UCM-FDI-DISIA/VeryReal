#include "Window.h"
#include <Ogre.h>
#include <SDL.h>
#include <OgreFileSystem.h>
#include <OgreFileSystemLayer.h>
#include <SDL_syswm.h>
#include <iostream>
using namespace VeryReal;
using namespace Ogre;
Window::Window():root(nullptr),render_system(nullptr),scene_manager(nullptr), name(""),config_route(""),sdl_window(nullptr),file_system_layer(nullptr),ogre_window(nullptr), window_height(0),window_width(0) {
 
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

bool Window::Init(Ogre::Root* root, Ogre::RenderSystem* render_system, Ogre::SceneManager* scene_manager) {
    this->root = root;
    this->render_system = render_system;
    this->scene_manager = scene_manager;   
    return true;
}
void  Window::demo(){

    //ESTO NO VA AQUI ES SOLO PARA LA DEMO
    
    //asignamos la 
    std::string ruta = config_route + "\\..\\Assets";
    Ogre::ResourceGroupManager::getSingleton().addResourceLocation(ruta, "FileSystem");
    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
    //luz principal
    Ogre::Light* light = scene_manager->createLight("LuzPrincipal");
    Ogre::SceneNode* lightNode = scene_manager->getRootSceneNode()->createChildSceneNode();
    lightNode->setPosition(-10, 0, 0);
    lightNode->attachObject(light);

   

    //cargamos sinbad SOLO SE PUEDEN CARGAR .MESH
    Ogre::Entity* ent = scene_manager->createEntity("Sinbad.mesh");
    Ogre::SceneNode* node = scene_manager->getRootSceneNode()->createChildSceneNode();
    node->attachObject(ent);
    //BUCLE PARA QUE NO SE CIERRE LA VENANA SE TIENE QUE QUITAR
    root->startRendering();

}
bool  Window::CreateWindoww() {
   
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
    if (sdl_window == NULL) {
        #ifdef DEBUG_MODE
        cerr << DEBUG_CREATEWINDOW_ERROR;
        #endif

        return false;
    }
    SDL_SysWMinfo wmInfo;
    SDL_VERSION(&wmInfo.version);
    SDL_GetWindowWMInfo(sdl_window, &wmInfo);//obtenemos la info de la ventana que acabamos de cerar con sdl para ahora pasarsela a ogre como ventana externa 
    
    miscParams["externalWindowHandle"] = Ogre::StringConverter::toString(size_t(wmInfo.info.win.window));
    //pasamos los valores a una ventana de ogre a partir de la ventana de sdl creada
    ogre_window = root->createRenderWindow(name, window_width, window_height, false, &miscParams);//siempre funciona segun la documentacion
   // return sdl_window;
    return true;
}


void Window::Update() {
    root->renderOneFrame();
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