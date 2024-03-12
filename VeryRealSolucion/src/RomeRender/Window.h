#pragma once
#include <string>
struct SDL_Window;

namespace Ogre {

	class SceneManager;
	class RenderSystem;
	class RenderWindow;
	class FileSystemLayer;
	class Root;

}
namespace VeryReal {
	//clase para crear una ventana en nuestro motor
	class Window
	{
		public:
			// <summary>
			/// Método que inicializa los valores de la clase
			/// </summary>
			/// <param name="root">Raiz de ogre.</param>

			Window(Ogre::Root* root, Ogre::RenderSystem* render_system, Ogre::SceneManager* scene_manager);
			// <summary>
			/// Destructora.Elimina la ventana y desactiva el modulo de video de sdl
			/// </summary>

			~Window();
			// <summary>
			/// Método que crea la ventana inicializando el modulo de SDL.
			/// Se crea una ventana con sdl y luego se le pasa a ogre. 
			/// Por ahora se cargan aqui los plguings de renderizado de ogre (no irán aqui en un futuro)
			/// </summary>
			//<returns> un puntero a la ventana creada con sdl
			void  CreateWindoww();
			void Init();//ira fuera
			// <summary>
			///Actualiza la ventana en caso de cerrarla,camviarla de tamaño y así
			/// </summary>

			void Update();
			void demo();
			// <summary>
			/// Método que devuelve un puntero a la ventana de sdl
			/// </summary>
			/// <returns>Puntero a la ventana de SDL.</returns>
			SDL_Window*  GetSDLWindow();
			// <summary>
			/// Método que devuelve un puntero a la ventana de ogre
			/// </summary>
			/// <returns>Puntero a la ventana de ogre.</returns>
			Ogre::RenderWindow* GetOgreWindow();
		private:
			Ogre::SceneManager* scene_manager;        
			Ogre::RenderSystem* render_system;    
			Ogre::RenderWindow* ogre_window;  
			std::string ruta_configuracion;
			std::string name;
			// Ventana
			int window_width;
			int window_height;
			SDL_Window* sdl_window;
			Ogre::FileSystemLayer* file_system_layer;
			Ogre::Root* root;
	};
}

