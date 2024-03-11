#ifndef RENDERMANAGER
#define RENDERMANAGER


#include "Manager.h"
#include "Vector3.h"
#include "string"

namespace VeryReal {

	class Window;
	class Light;
	class MeshRender;
	class Camera;
	class Animator;
	class SGTechniqueResolverListener;

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
	namespace RTShader {
		class ShaderGenerator;
	}
}

namespace VeryReal {
	// Declaraci�n de la clase RenderManager, que hereda de Manager
	class RenderManager : public Manager<RenderManager> {
	public:
		// Constructor de la clase RenderManager
		RenderManager();

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
		Ogre::SceneNode* CreateNode();

		// Crea un nodo de escena secundario y lo adjunta al nodo proporcionado
		// @param nod Nodo de escena al que se adjuntar� el nuevo nodo secundario
		// @return Puntero al nodo de escena secundario creado
		Ogre::SceneNode* CreateChildSceneNode(Ogre::SceneNode* nod);

		// Elimina un nodo de escena de Ogre
		// @param nod Puntero al nodo de escena que se eliminar�
		void DeleteNode(Ogre::SceneNode* nod);
		
		Ogre::RenderWindow* GetRenderWindow();
		Ogre::SceneManager* SceneManagerOgree();
		// Capa del sistema de archivos de Ogre
		Ogre::FileSystemLayer* filesystemlayer_;
	protected:
		// Puntero a la ventana de la aplicaci�n
		VeryReal::Window* window_;

		// Nombre de la aplicaci�n
		std::string appname_;

		

		// Administrador de escena de Ogre
		Ogre::SceneManager* scenemanager_;

		// Sistema de renderizado de Ogre
		Ogre::RenderSystem* rendersystem_;

		// Ruta de configuraci�n
		std::string cfgPath_;

		// Ra�z de Ogre
		Ogre::Root* root_;

		// Escuchador de resoluci�n de t�cnicas ShaderGenerator
		VeryReal::SGTechniqueResolverListener* materialListener_;

		// Generador de shaders RTShader
		Ogre::RTShader::ShaderGenerator* shaderGenerator;

		// Ventana de visualizaci�n
		Ogre::Viewport* viewport_;

		// Carga los recursos necesarios para la aplicaci�n
		void LoadResources();

		// Carga los shaders necesarios para la aplicaci�n
		void LoadShaders();

		// Descarga los shaders cargados previamente
		void UnloadShaders();
	};
}

#endif // !RENDERMANAGER
