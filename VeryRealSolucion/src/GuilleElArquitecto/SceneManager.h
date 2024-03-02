#pragma once
#include "Manager.h"
#include "Scene.h"
#include <list>
using namespace std;

class SceneManager:public Manager<SceneManager>
{
private:
	//lista con todas la escenas
	list<Scene*> scenes_list;
public:
	SceneManager();
	virtual ~SceneManager();

	void Update(const double& dt);
	//si hay escenas que quieren ser eliminadas las removemos aquí
	//esto elimina de manera más segura las escenas
	void Refresh();

	Scene* AddScene(scene_name name);
	void RemoveScene(scene_name name);

	void ActivationScene(scene_name name, bool active);
	void EliminationScene(scene_name name, bool to_eliminate);
};

