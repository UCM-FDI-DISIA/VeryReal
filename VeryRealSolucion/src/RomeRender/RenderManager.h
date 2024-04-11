#pragma once
#ifndef RENDERMANAGER
#define RENDERMANAGER

#include "Manager.h"
#include "Vector3.h"
#include "string"
#include "export.h"

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
	class ManualObject;
	class Viewport;
    class Entity;
	namespace RTShader {
		class ShaderGenerator;
	}
}

namespace VeryReal {
	// Declaraci�n de la clase RenderManager, que hereda de Manager
	class /*VERYREAL_API*/ RenderManager : public Manager<RenderManager> {
               
                
	public: 
		
		// Constructor de la clase RenderManager
		RenderManager() { }

		// Destructor virtual de la clase RenderManager
		virtual ~RenderManager();

		// Inicializa el administrador de renderizado con el nombre proporcionado
		// @param name Nombre de la aplicaci�n
		virtual void InitManager(std::string const& name);

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
		
		Ogre::RenderWindow* GetRenderWindow();
        Ogre::Root* GetRenderRoot();
		Ogre::SceneManager* SceneManagerOgree();
		// Capa del sistema de archivos de Ogre
		Ogre::FileSystemLayer* filesystem_layer;
	protected:
		// Puntero a la ventana de la aplicaci�n
		VeryReal::Window* window;

		// Nombre de la aplicaci�n
		std::string appname;

		// Administrador de escena de Ogre
		Ogre::SceneManager* scene_manager;

		// Sistema de renderizado de Ogre
		Ogre::RenderSystem* render_system;

		// Ruta de configuraci�n
		std::string cfgPath;

		// Ra�z de Ogre
		Ogre::Root* root;

		// Escuchador de resoluci�n de t�cnicas shader_generator
		VeryReal::SGTechniqueResolverListener* material_listener	;

		// Generador de shaders RTShader
		Ogre::RTShader::ShaderGenerator* shader_generator;


		// Ventana de visualizaci�n
		Ogre::Viewport* viewport;

		// Carga los recursos necesarios para la aplicaci�n
		void LoadResources();

		// Carga los shaders necesarios para la aplicaci�n
		void LoadShaders();

		// Descarga los shaders cargados previamente
		void UnloadShaders();
	};
}

#endif // !RENDERMANAGER
