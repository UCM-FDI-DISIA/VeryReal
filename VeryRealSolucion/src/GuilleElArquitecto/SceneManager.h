#pragma once
#ifndef SCENEMANAGER
#define SCENEMANAGER
#include "Manager.h"
#include <list>
#include <string>

using scene_name = std::string;

#pragma warning(disable : 4251)

namespace VeryReal {
	class Scene;
	class  SceneManager : public VeryReal::Manager<SceneManager> {
	private:
		//lista con todas la escenas
		std::list<VeryReal::Scene*> scenes_list;
		SceneManager(){};
  
	public:
        static bool Init() {
        VeryReal::SceneManager* sm = new VeryReal::SceneManager();
            if (sm != nullptr) {
                InitPointer(&sm);
                //aqui no habria que eliminar creator?
                return true;
            }
            return false;   // Si el constructor devuelve nullptr, la construcción falló
        }
		virtual ~SceneManager();

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