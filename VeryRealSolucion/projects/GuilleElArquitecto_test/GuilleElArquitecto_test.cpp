#include <iostream>
#include <ErrorInformant.h>
#include "Creator.h"
#include "TransformComponent.h"
#include "CreatorTransformComponent.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Entity.h"

using namespace VeryReal;
int main()
{
    //Primer argumento, el nombre del aviso.
    //Segundo argumento la descripcion
    //Tercer argumento el tipo de aviso
    //Ultimo argumento las opciones
    //Devuelve un entero que determina que opcion ha seleccionado el usuario
    /*cout << ErrorInf().showErrorMessageBox("test", "do", EI_WARNING, EI_W_RETRY) << endl;
    std::cout << "Hello World!\n";*/
 
    //prueba funcional
   /* VeryReal::Creator::Instance()->AddCreator("TransformComponent", new VeryReal::CreatorTransformComponent());
    Scene* s =SceneManager::Instance()->AddScene("Play",true);
    s = SceneManager::Instance()->GetScene("Play");
    VeryReal::Entity* e = s->AddEntity("Player");
    Component* c=e->AddComponent("TransformComponent");
    std::cout << SceneManager::Instance()->GetScene("Play")->GetEntity("Player")->HasComponent("TransformComponent") << "\n";*/

    bool t=VeryReal::Creator::Init();
    VeryReal::SceneManager::Init();
    if (t) {
        std::cout << "true";
    }
    else {
    
        std::cout << "false";
    }
    VeryReal::Creator::Instance()->AddCreator("TransformComponent", new VeryReal::CreatorTransformComponent());
    Scene* s = SceneManager::Instance()->AddScene("Play", true);
    VeryReal::Entity* e = s->AddEntity("Player");
    Component* c= e->AddComponent("TransformComponent");
    std::cout << SceneManager::Instance()->GetScene("Play")->GetEntity("Player")->HasComponent("TransformComponent") << "\n";

}

