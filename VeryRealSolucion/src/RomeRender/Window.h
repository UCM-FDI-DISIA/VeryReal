#pragma once
#include <string>
class SDL_Window;

namespace Ogre {

	class SceneManager;
	class RenderSystem;
	class RenderWindow;
	class FileSystemLayer;
	class Root;

}
namespace VeryReal {
	using namespace Ogre;
	using namespace std;
	class Window
	{
		public:
			Window();
			void init();
			~Window();
		private:
			Ogre::SceneManager* scene_manager;        
			Ogre::RenderSystem* render_system;    
			Ogre::RenderWindow* ogre_window;  
			string ruta_configuracion;
			string name;
			// Ventana
			int window_width, window_height;
			SDL_Window* sdl_window;
			FileSystemLayer* file_system_layer;
	};
}

