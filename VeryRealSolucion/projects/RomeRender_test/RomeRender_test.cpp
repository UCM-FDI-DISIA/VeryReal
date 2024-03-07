// RomeRender_test.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <RenderManager.h>
#include <Entity.h>
#include <TransformComponent.h>
#include <CreatorTransformComponent.h>
#include <Camera.h>
#include <Light.h>
#include <MeshRender.h>
#include <Animator.h>

#include <ErrorInformant.h>
#include "Creator.h"
#include "CreatorTransformComponent.h"
#include "SceneManager.h"
#include "Scene.h"
#include "CreatorLightComponent.h"
#include "CreatorAnimatorComponent.h"
#include "CreatorCameraComponent.h"
#include "CreatorMeshRenderComponent.h"

using namespace VeryReal;
int main()
{

   VeryReal::RenderManager::Instance()->InitManager("app");
   VeryReal::Entity sinbad;
   VeryReal::Creator::Instance()->AddCreator("transform", new VeryReal::CreatorTransformComponent());
   VeryReal::Creator::Instance()->AddCreator("MeshRender", new VeryReal::CreatorMeshRenderComponent());
   VeryReal::Creator::Instance()->AddCreator("Animator", new VeryReal::CreatorAnimatorComponent());
  VeryReal::Creator::Instance()->AddCreator("Camera", new VeryReal::CreatorCameraComponent());
  VeryReal::Creator::Instance()->AddCreator("Light", new VeryReal::CreatorLightComponent());
   Scene* s = SceneManager::Instance()->AddScene("Play");
   s = SceneManager::Instance()->GetScene("Play");
   Entity* e = s->AddEntity("Player");
   Entity* camara = s->AddEntity("Cam");
  Component*cam= camara->AddComponent("Camera");

  static_cast<Camara*>(cam)->InitComponent("hola", Vector3(0.8, 0.3, 1), VeryReal::RenderManager::Instance()->GetRenderWindow(), VeryReal::RenderManager::Instance()->SceneManagerOgree(), Vector3(10, 0, 0));


   Component* c = e->AddComponent("transform");
   c->SetEntity(e);
  // e->AddComponent("Animator");
   Component* t=e->AddComponent("MeshRender");
   Component* ligh = e->AddComponent("Light");
   ligh->SetEntity(e);
   static_cast<Light*>(ligh)->InitComponent(1, Vector3(0.4, 1, 0.6), 25, 25, 90, 180, 0.1, true);
   Component* animator = e->AddComponent("Animator");
   animator->SetEntity(e);
  
   //MOMENTANEO
   static_cast<MeshRender*>(t)->InitComponent(false, "sinbad", "hola", "Sinbad.mesh", VeryReal::RenderManager::Instance()->CreateNode(),
       VeryReal::RenderManager::Instance()->SceneManagerOgree(), VeryReal::RenderManager::Instance()->filesystemlayer_);
   cout << SceneManager::Instance()->GetScene("Play")->GetEntity("Player")->HasComponent("transform") << "\n";
   static_cast<Animator*>(animator)->InitComponent(VeryReal::RenderManager::Instance()->SceneManagerOgree(), "hola", static_cast<TransformComponent*>(c), static_cast<MeshRender*>(t));
    while (true) {
        VeryReal::RenderManager::Instance()->Update(0.2);


        e->Update();
        cam->Update();


    }
    return 1;
}

// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
