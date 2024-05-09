#pragma once
#ifndef SCENEMANAGER
#define SCENEMANAGER
#include "Manager.h"
#include <list>
#include <string>

using scene_name = std::string;

#pragma warning(disable : 4251)
/*
    Manager que se encarga de gestionar las escenas, previamente leidas por el ScriptManager.
    Para ello recorrera todas las escenas activas en su Update actualizandolas, estas escenas actualizaran las entidades que poseen y las entidades actualizaran los componentes.
    Tambien posee un metodo Refresh el cual se encarga de eliminar las escenas marcadas para eliminar.
*/
namespace VeryReal {
class Scene;
class VERYREAL_GUILLEELARQUITECTO SceneManager : public VeryReal::Manager<SceneManager> {
        private:
    //lista con todas la escenas
    std::list<VeryReal::Scene*> scenes_list;
    SceneManager(){};

        public:
    static std::pair<bool,std::string> Init() {
        SceneManager* a = new SceneManager();
        if (a != nullptr) {
            instance_pointer.reset(a);
            return {true, "SceneManager pointer sucesfully initialized"};
        }
        return {false, "SceneManager pointer a problem while it was initializing"};
    }
    virtual ~SceneManager();

    // Actualiza las escenas
    void Update(const double& dt);

    // Si hay escenas que quieren ser eliminadas las removemos aquí
    void Refresh();

    // Añade una escena.
    // Este metodo se llama desde el ScriptManager al leer una escena.
    VeryReal::Scene* AddScene(scene_name name, bool active);

    // Elimina una escena y devuelve el iterador que describe la posición de la siguiente escena.
    std::list<VeryReal::Scene*>::iterator RemoveScene(std::list<VeryReal::Scene*>::iterator scene);

    // Activa una escena
    void ActivationScene(scene_name name, bool active);
    
    // Marca para eliminar una escena
    void EliminationScene(scene_name name, bool to_eliminate);

    // Si existe la escena la devuelve si no devuelve nullptr
    Scene* GetScene(scene_name name);
    bool HasScene(scene_name name);

    // Devuelve la escena activa
    Scene* GetActiveScene();
};
}

#pragma warning(default : 4251)

#endif