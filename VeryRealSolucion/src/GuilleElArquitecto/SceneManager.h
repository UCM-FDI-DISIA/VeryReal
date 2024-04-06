#pragma once
#ifndef SCENEMANAGER
#define SCENEMANAGER
#include "Manager.h"
#include <list>
#include <string>
#include "export.h"
using scene_name = std::string;

#pragma warning(disable : 4251)

namespace VeryReal {
	class Scene;
	class VERYREAL_API SceneManager : public VeryReal::Manager<SceneManager> {
	private:
		//lista con todas la escenas
		std::list<VeryReal::Scene*> scenes_list;
	public:
        SceneManager(){};
		virtual ~SceneManager(){};

		void Update(const double& dt);
		//si hay escenas que quieren ser eliminadas las removemos aquí
		//esto elimina de manera más segura las escenas
		void Refresh();

		VeryReal::Scene* AddScene(scene_name name,bool active);
		void RemoveScene(scene_name name);

		void ActivationScene(scene_name name, bool active);
		void EliminationScene(scene_name name, bool to_eliminate);
		//si existe la escen la devuleve si no devuelve nullptr
		Scene* GetScene(scene_name name);
		bool HasScene(scene_name name);
	};
}

#pragma warning(default : 4251)

#endif