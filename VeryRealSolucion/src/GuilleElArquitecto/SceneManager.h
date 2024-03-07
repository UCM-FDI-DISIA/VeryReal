#pragma once
#ifndef SCENEMANAGER
#define SCENEMANAGER
#include "Manager.h"
#include <list>
#include <string>
using namespace std;
using scene_name = string;
namespace VeryReal {
	class Scene;
	class SceneManager :public VeryReal::Manager<SceneManager>
	{
	private:
		//lista con todas la escenas
		list<VeryReal::Scene*> scenes_list;
	public:
		/*SceneManager();
		virtual ~SceneManager();*/

		void Update(const double& dt);
		//si hay escenas que quieren ser eliminadas las removemos aquí
		//esto elimina de manera más segura las escenas
		void Refresh();

		VeryReal::Scene* AddScene(scene_name name);
		void RemoveScene(scene_name name);

		void ActivationScene(scene_name name, bool active);
		void EliminationScene(scene_name name, bool to_eliminate);

		Scene* GetScene(scene_name name);
	};
}
#endif

