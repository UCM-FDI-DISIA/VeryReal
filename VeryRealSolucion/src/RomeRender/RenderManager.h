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
	class RenderManager :public Manager<RenderManager> {

	public:

		RenderManager();
		virtual ~RenderManager();
		virtual void InitManager(std::string const& name);
		virtual void Update(const double& dt);

		Ogre::SceneNode* CreateNode();
		Ogre::SceneNode* CreateChildSceneNode(Ogre::SceneNode* nod);
		void DeleteNode(Ogre::SceneNode* nod);

	protected:
		VeryReal::Window* window_;
		std::string appname_;
		Ogre::FileSystemLayer* filesystemlayer_;
		Ogre::SceneManager* scenemanager_;
		Ogre::RenderSystem* rendersystem_;
		std::string cfgPath_;
		Ogre::Root* root_;
		VeryReal::SGTechniqueResolverListener* materialListener_;
		Ogre::RTShader::ShaderGenerator* shaderGenerator;
		Ogre::Viewport* viewport_;


		void LoadResources();
		void LoadShaders();
		void UnloadShaders();
	};



}


#endif // !RENDERMANAGER
