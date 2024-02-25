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

Window::Window() {
    name = "VeryReall";
}

Window::~Window() {

}
void Window::init() {
    // creamos un nuevo filesystem layer
    file_system_layer = new Ogre::FileSystemLayer("VeryReal"); 
    Ogre::String plugins_path;
    //asignamos la ruta para las configuraciones de la pantalla
    ruta_configuracion = file_system_layer->getConfigFilePath("plugins.cfg");
    //  FALTA TRATAMIENTO DE ERROR SU NO EXISTE ruta_configuracion
    file_system_layer->setHomePath(ruta_configuracion);
    Ogre::Root* root = new Ogre::Root();
    //obtenermos el render system de tipo GL (los datos se descargan en el .bat)
    root->loadPlugin("RenderSystem_GL");
    Ogre::RenderSystem* renderSystem = root->getRenderSystemByName("GL Rendering Subsystem");
    const Ogre::RenderSystemList renderSystems = root->getAvailableRenderers();
    //cogemos el primer elemento del vector de render systems
    render_system = renderSystems.front();
    root->setRenderSystem(render_system);
    root->initialise(false);
    //inicializamos sdl
    SDL_Init(SDL_INIT_EVERYTHING);
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
    SDL_GetWindowWMInfo(sdl_window, &wmInfo);
    miscParams["externalWindowHandle"] = Ogre::StringConverter::toString(size_t(wmInfo.info.win.window));
    //pasamos los valores a una ventana de ogre a partir de la ventana de sdl creada
    ogre_window = root->createRenderWindow(name, window_width, window_height, false, &miscParams);
    scene_manager = root->createSceneManager();
    render_system->_initRenderTargets();

    //BUCLE PARA QUE NO SE CIERRE LA VENANA SE TIENE QUE QUITAR
    while(true) {

    }
}