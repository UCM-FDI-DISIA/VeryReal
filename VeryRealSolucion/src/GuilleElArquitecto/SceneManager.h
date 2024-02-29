#pragma once
#include "Manager.h"
#include "Scene.h"
#include <list>

class SceneManager:public Manager
{
private:
	list<Scene*> scenes_list;
public:
	SceneManager();
	virtual ~SceneManager();
	void Update(const double& dt);
	void Refresh();

	Scene* AddScene(scene_name name);
	void RemoveScene(scene_name name);

	void ActivationScene(scene_name name, bool active);
	void EliminationScene(scene_name name, bool to_eliminate);
};

