#pragma once
#include <string>
#include "export.h"
struct SDL_Window;

namespace Ogre {
	class SceneManager;
	class RenderSystem;
	class RenderWindow;
	class FileSystemLayer;
	class Root;
        class RenderTarget;
        }

#pragma warning(disable : 4251)

namespace VeryReal {
	//clase para crear una ventana en nuestro motor
    class VERYREAL_API Window {
            public:
        // <summary>
        /// Método que inicializa los valores de la clase
        /// </summary>
        Window();

        // <summary>
        /// Destructora.Elimina la ventana y desactiva el modulo de video de sdl
        /// </summary>
        virtual ~Window();

        // <summary>
        /// Método que crea la ventana inicializando el modulo de SDL.
        /// Se crea una ventana con sdl y luego se le pasa a ogre.
        /// Por ahora se cargan aqui los plguings de renderizado de ogre (no irán aqui en un futuro)
        /// </summary>
        //<returns> un puntero a la ventana creada con sdl
        bool CreateWindoww();
        bool Init(Ogre::Root* root, Ogre::RenderSystem* render_system, Ogre::SceneManager* scene_manager);   //ira fuera
        
        // <summary>
        ///Actualiza la ventana en caso de cerrarla,camviarla de tamaño y así
        /// </summary>
        void Update(const double& dt);
        // <summary>
        /// Método que devuelve un puntero a la ventana de sdl
        /// </summary>
        /// <returns>Puntero a la ventana de SDL.</returns>
        SDL_Window* GetSDLWindow();
        // <summary>
        /// Método que devuelve un puntero a la ventana de ogre
        /// </summary>
        /// <returns>Puntero a la ventana de ogre.</returns>
        Ogre::RenderWindow* GetOgreWindow();

        private:
        Ogre::SceneManager* scene_manager;
        Ogre::RenderSystem* render_system;
        Ogre::RenderWindow* ogre_window;
        std::string config_route;
        std::string name;
        // Ventana
        int window_width;
        int window_height;
        SDL_Window* sdl_window;
        Ogre::FileSystemLayer* file_system_layer;
        Ogre::Root* root;
        Ogre::RenderTarget* r;
    };
}

#pragma warning(disable : 4251)