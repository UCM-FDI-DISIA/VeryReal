#pragma once
#ifndef RENDERMANAGER
#define RENDERMANAGER

#include "Manager.h"
#include "Vector3.h"
#include "string"
#include "exportRomeRender.h"
//#include "SceneManager" 

#define DEBUG_ROOT_ERROR "OGRE NO HA SIDO INICIALIZADO CORRECTAMENTE\n"
#define DEBUG_OGRE_ERROR "NO SE HA ENCONTRADO EL ARCHIVO ogre.cfg\n"
#define DEBUG_PLUGINS_ERROR "NO SE HA ENCONTRADO EL ARCHIVO  plugins.cfg\n"
#define DEBUG_RESOURCES_ERROR "NO SE HA ENCONTRADO EL ARCHIVO  resources.cfg\n"
#define DEBUG_WINDOW_ERROR "NO SE HA PODIDO CREAR LA VENTANA\n"

namespace VeryReal {
	class Window;
	class Light;
	class MeshRender;
	class Camera;
	class Animator;
	class SGTechniqueResolverListener;
        class Entity;
 }

namespace Ogre {
	class SceneNode;
	class Node;
	class FileSystemLayer;
	class Root;
	class SceneManager;
	class RenderSystem;
	class RenderWindow;
    class OverlayManager;
    class OverlaySystem;
	class ManualObject;
	class Viewport;
    class Entity;
}

#pragma warning(disable : 4251)

namespace VeryReal {
	// Declaraci�n de la clase RenderManager, que hereda de Manager

	class VERYREAL_ROMERENDER RenderManager : public Manager<RenderManager> {
               
    private:
                RenderManager() { }
	public: 
		
		// Constructor de la clase RenderManager
		 Ogre::SceneManager* getSceneManager();
         Ogre::ManualObject*  createManualObject(Ogre::SceneNode* node);
         void destroyManualObject(Ogre::ManualObject* const object);
       
		static std::pair<bool,std::string> Init() {
			RenderManager* a = new RenderManager();
			if (a != nullptr) {
				instance_pointer.reset(a);
                std::pair<bool, std::string> r = a->InitManager("JUEGO");   //inicializamos el manager
				if (!r.first) {
					delete a;   //el init manager da error pero se tiene que destruir memoria
                   return {false, "pointer had a problem while it was initializing"};
				}
				return {true, "RenderManager pointer sucesfully initialized"};
			}
			return {false, "RenderManager pointer had a problem while it was initializing"};
		}

		// Destructor virtual de la clase RenderManager
        virtual ~RenderManager();

		// Inicializa el administrador de renderizado con el nombre proporcionado
		// @param name Nombre de la aplicaci�n
        virtual std::pair<bool, std::string> InitManager(std::string const& name);

		// Actualiza el administrador de renderizado con el paso de tiempo proporcionado
		// @param dt Paso de tiempo desde la �ltima actualizaci�n
         virtual void Update(const double& dt);

		// Crea un nodo de escena en Ogre y devuelve un puntero a �l
		// @return Puntero al nodo de escena creado
		Ogre::SceneNode* CreateNode(VeryReal::Vector3 vec = Vector3(0, 0, 0));

		// Crea un nodo de escena secundario y lo adjunta al nodo proporcionado
		// @param nod Nodo de escena al que se adjuntar� el nuevo nodo secundario
		// @return Puntero al nodo de escena secundario creado
		Ogre::SceneNode* CreateChildSceneNode(Ogre::SceneNode* nod, VeryReal::Vector3 vec=Vector3(0,0,0));

		// Elimina un nodo de escena de Ogre
		// @param nod Puntero al nodo de escena que se eliminar�
		void DeleteNode(Ogre::SceneNode* nod);
        void DeleteEntity(Ogre::Entity* nod);
		

		/// <summary>
		/// ESTO ESTA MAL LINEA ROJA HAY QUE QUITAR ESTE EXPORT Y SEGURAMENTE CREARSE LA CLASE NODE
		/// </summary>
		/// <returns></returns>
		Ogre::RenderWindow* GetRenderWindow();
         Ogre::Root* GetRenderRoot();
		Ogre::SceneManager* SceneManagerOgree();
        Ogre::OverlayManager* GetOverlayManager();
        Ogre::OverlaySystem* GetOverlaySystem();
		VeryReal::Window* GetVRWindow();

		// Capa del sistema de archivos de Ogre
		Ogre::FileSystemLayer* filesystem_layer = nullptr;

	protected:
		// Puntero a la ventana de la aplicaci�n
		VeryReal::Window* window = nullptr;

		// Nombre de la aplicaci�n
        std::string appname = "";

		// Administrador de escena de Ogre
		Ogre::SceneManager* scene_manager = nullptr;

		// Sistema de renderizado de Ogre
		Ogre::RenderSystem* render_system = nullptr;

		//Manager del sistema de overlay de ogre
        Ogre::OverlayManager* overlay_manager = nullptr;

		//Sistema de overlay de Ogre
        Ogre::OverlaySystem* overlay_system = nullptr;

		// Ruta de configuraci�n
        std::string cfgPath = "";

		// Ra�z de Ogre
        Ogre::Root* root = nullptr;

		// Ventana de visualizaci�n
        Ogre::Viewport* viewport = nullptr;

		// Carga los recursos necesarios para la aplicaci�n
        void  LoadResources();
	};
}

#pragma warning(default : 4251)

#endif // !RENDERMANAGER
