#pragma once
#ifndef SCENEMANAGER
#define SCENEMANAGER
#include "Manager.h"
#include "Scene.h"
#include <list>
using namespace std;

namespace VeryReal {
	class SceneManager :public VeryReal::Manager<SceneManager>
	{
	private:
		//lista con todas la escenas
		list<VeryReal::Scene*> scenes_list;
	public:
		SceneManager();
		virtual ~SceneManager();

		void Update(const double& dt);
		//si hay escenas que quieren ser eliminadas las removemos aqu�
		//esto elimina de manera m�s segura las escenas
		void Refresh();

		VeryReal::Scene* AddScene(scene_name name);
		void RemoveScene(scene_name name);

		void ActivationScene(scene_name name, bool active);
		void EliminationScene(scene_name name, bool to_eliminate);
	};
}
#endif

