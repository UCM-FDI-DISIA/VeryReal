// RomeRender_test.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
#pragma once
#include <iostream>
#include <RenderManager.h>
#include "CreatorAnimatorComponent.h"
#include "CreatorTransformComponent.h"
#include "Creator.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Entity.h"
#include "Component.h"
#include "CreatorCameraComponent.h"
#include "Vector3.h"
#include "CreatorLightComponent.h"
#include "CreatorMeshRenderComponent.h"
#include "UI/UISpriteRenderComponent.h" 


using namespace VeryReal;


int main() {
    //#pragma region Prueba Animator->FUNCIONA
//    VeryReal::Creator::Instance()->AddCreator("animator", new VeryReal::CreatorAnimatorComponent());
//    Creator::Instance()->GetCreator("animator")->AddParameter("name", "anim");
//
//
//   VeryReal::RenderManager::Instance()->InitManager("app");
//  VeryReal::Creator::Instance()->AddCreator("TransformComponent", new VeryReal::CreatorTransformComponent());
//   VeryReal::Creator::Instance()->AddCreator("MeshRenderComponent", new VeryReal::CreatorMeshRenderComponent());
//   Creator::Instance()->AddCreator("Animator", new CreatorAnimatorComponent());
//   //VeryReal::Creator::Instance()->AddCreator("Camera", new VeryReal::CreatorCameraComponent());
//   //VeryReal::Creator::Instance()->AddCreator("Light", new VeryReal::CreatorLightComponent());
//   /*Scene* s = SceneManager::Instance()->AddScene("Play");
//   s = SceneManager::Instance()->GetScene("Play");
//   Entity* e = s->AddEntity("Player");
//   Entity* luz = s->AddEntity("Luz");
//   Entity* camara = s->AddEntity("Cam");
//   Component*cam= camara->AddComponent("Camera");*/
//
//    Scene* s = SceneManager::Instance()->AddScene("Play");
//    s = SceneManager::Instance()->GetScene("Play");
//    VeryReal::Entity* e = s->AddEntity("Player");
//    Component* c = e->AddComponent("animator");
//    std::cout << SceneManager::Instance()->GetScene("Play")->GetEntity("Player")->HasComponent("animator") << "\n";


#pragma endregion

#pragma region Prueba Camara
    /*VeryReal::Creator::Instance()->AddCreator("camera", new VeryReal::CreatorCameraComponent());
    Creator::Instance()->GetCreator("camera")->AddParameter("name", std::string("anim"));
    Creator::Instance()->GetCreator("camera")->AddParameter("color", Vector3{100,100,100});
    Creator::Instance()->GetCreator("camera")->AddParameter("offset", Vector3{ 100,100,100 });


    Scene* s = SceneManager::Instance()->AddScene("Play");
    s = SceneManager::Instance()->GetScene("Play");
    VeryReal::Entity* e = s->AddEntity("Player");
    Component* c = e->AddComponent("camera");
    std::cout << SceneManager::Instance()->GetScene("Play")->GetEntity("Player")->HasComponent("camera") << "\n";*/

#pragma endregion

#pragma region Prueba Luz
 /*   VeryReal::RenderManager::Instance()->InitManager("app");
    VeryReal::Creator::Instance()->AddCreator("luz", new VeryReal::CreatorLightComponent());
    VeryReal::Creator::Instance()->AddCreator("TransformComponent", new VeryReal::CreatorTransformComponent());
    Creator::Instance()->GetCreator("luz")->AddParameter("type", 8);
    Creator::Instance()->GetCreator("luz")->AddParameter("diffusecolour", Vector3{ 100,100,100 });
    Creator::Instance()->GetCreator("luz")->AddParameter("shadowfardist", float(2.0));
    Creator::Instance()->GetCreator("luz")->AddParameter("shadowdist", float(2.0));
    Creator::Instance()->GetCreator("luz")->AddParameter("ineerangle", float(2.0));
    Creator::Instance()->GetCreator("luz")->AddParameter("outerangle", float(2.0));
    Creator::Instance()->GetCreator("luz")->AddParameter("nearclipdist", float(2.0));
    Creator::Instance()->GetCreator("luz")->AddParameter("shdws", true);

    Scene* s = SceneManager::Instance()->AddScene("Play", true);
    s = SceneManager::Instance()->GetScene("Play");
    VeryReal::Entity* e = s->AddEntity("Luzent");
    
    Component* c = e->AddComponent("luz"); 
    Component* d = e->AddComponent("TransformComponent");
    std::cout << SceneManager::Instance()->GetScene("Play")->GetEntity("Luzent")->HasComponent("luz") << "\n";*/

#pragma endregion

   
   VeryReal::RenderManager::Instance()->InitManager("app");
   //VeryReal::Creator::Instance()->AddCreator("TransformComponent", new VeryReal::CreatorTransformComponent());
   //Creator::Instance()->GetCreator("TransformComponent")->AddParameter("a", 0);
   //Creator::Instance()->GetCreator("TransformComponent")->AddParameter("position", Vector3{0, 0, 20});
   //Creator::Instance()->GetCreator("TransformComponent")->AddParameter("rotation", Vector3{0, 0, 0});
   //Creator::Instance()->GetCreator("TransformComponent")->AddParameter("scale", Vector3{1, 1, 1});

   //VeryReal::Creator::Instance()->AddCreator("MeshRenderComponent", new VeryReal::CreatorMeshRenderComponent());
   //Creator::Instance()->GetCreator("MeshRenderComponent")->AddParameter("isstatic", true);
   //Creator::Instance()->GetCreator("MeshRenderComponent")->AddParameter("modelname", std::string("Sinbad.mesh"));
   //Creator::Instance()->GetCreator("MeshRenderComponent")->AddParameter("entityname", std::string( "sinbad"));
   //Creator::Instance()->GetCreator("MeshRenderComponent")->AddParameter("materialname", std::string(""));
   //#pragma region camara
   //VeryReal::Creator::Instance()->AddCreator("Camera", new VeryReal::CreatorCameraComponent());
   //Creator::Instance()->GetCreator("Camera")->AddParameter("name", std::string("anim"));
   //Creator::Instance()->GetCreator("Camera")->AddParameter("color", Vector3(0.8f, 0.3f, 1));
   //Creator::Instance()->GetCreator("Camera")->AddParameter("offset", Vector3{100, 100, 100});
   //#pragma endregion
   //#pragma region luz
   //VeryReal::Creator::Instance()->AddCreator("Light", new VeryReal::CreatorLightComponent());
   //Creator::Instance()->GetCreator("Light")->AddParameter("type", 1);
   //Creator::Instance()->GetCreator("Light")->AddParameter("diffusecolour", Vector3{1, 1, 1});
   //Creator::Instance()->GetCreator("Light")->AddParameter("shadowfardist", float(25.0));
   //Creator::Instance()->GetCreator("Light")->AddParameter("shadowdist", float(25.0));
   //Creator::Instance()->GetCreator("Light")->AddParameter("ineerangle", float(90.0));
   //Creator::Instance()->GetCreator("Light")->AddParameter("outerangle", float(180.0));
   //Creator::Instance()->GetCreator("Light")->AddParameter("nearclipdist", float(0.1));
   //Creator::Instance()->GetCreator("Light")->AddParameter("shdws", true);
   //#pragma endregion 
   // 
   //VeryReal::Scene* s = SceneManager::Instance()->AddScene("Play",true);
   //s = SceneManager::Instance()->GetScene("Play");
   //Entity* e = s->AddEntity("Player");

   UiSpriteRenderer* prueba = new UiSpriteRenderer();
    prueba->demo();
   //Entity* luz = s->AddEntity("Luz");
   //Entity* camara = s->AddEntity("Cam");
   //Component*cam= camara->AddComponent("Camera");
   //Component* trans = luz->AddComponent("TransformComponent");
   //Component* luzcom = luz->AddComponent("Light");
   //Component* transform = e->AddComponent("TransformComponent");
   //Component* meshrenderer = e->AddComponent("MeshRenderComponent");

   while (true) {
       VeryReal::RenderManager::Instance()->Update(0.2);
      
       //s->Update(0.1);


   }



  // }
       VeryReal::RenderManager::Instance()->~RenderManager();
  // delete s;
   return 1;

 ///* static_cast<CameraComponent*>(cam)->InitComponent("hola", Vector3(0.8, 0.3, 1), 
 //  VeryReal::RenderManager::Instance()->GetRenderWindow(), VeryReal::RenderManager::Instance()->SceneManagerOgree(), Vector3(10, 0, 0));*/


 //  Component* c = e->AddComponent("TransformComponent");
 //  Component* t=e->AddComponent("MeshRenderComponent");


 // /* Component* transluz=  luz->AddComponent("TransformComponent");
 //  static_cast<TransformComponent*>(transluz)->SetPosition(static_cast<TransformComponent*>(transluz)->GetPosition()- Vector3(400,-600,0));
 //  Component* ligh = luz->AddComponent("Light");
 //  ligh->SetEntity(luz);
 //  static_cast<Light*>(ligh)->InitComponent(1, Vector3(1, 1, 1), 25, 25, 90, 180, 0.1, true);


 //  Component* animator = e->AddComponent("Animator");*/

 //  //animator->SetEntity(e);
 // 
 //  //MOMENTANEO

 //  static_cast<MeshRenderComponent*>(t)->InitComponent(false, "Sinbad.mesh", "hola", "Ogre/Skin", VeryReal::RenderManager::Instance()->CreateNode(),
 //      VeryReal::RenderManager::Instance()->SceneManagerOgree(), VeryReal::RenderManager::Instance()->filesystem_layer);

 //  std::cout << SceneManager::Instance()->GetScene("Play")->GetEntity("Player")->HasComponent("TransformComponent") << "\n";

 //  //init, create, play
 // //bool p= static_cast<AnimatorComponent*>(animator)->InitComponent("hola");
 //  //static_cast<Animator*>(animator)->createAnimation("Sinbad.skeleton", 0.10);
 //  //static_cast<AnimatorComponent*>(animator)->setAnimation("Dance", true, true);
 //  //unsigned long long  m_initTime = GetTickCount64();
 //  //auto time = m_initTime;
 //  ////tiempo actual- el tiempo de inicio - el tiempo desde anterior;
 //  //auto dt =( GetTickCount64() - m_initTime)-time;
 //  // while (true) {
 //  //      dt = (GetTickCount64() - m_initTime) - time;
 //  //      time = (GetTickCount64() - m_initTime);
 //  //     e->Update(dt);
 //  //     luz->Update(dt);
 //  //     camara->Update(dt);
 //  //     VeryReal::RenderManager::Instance()->Update(0.2);

 //  // }
 //   return 1;
}

// Ejecutar programa: Ctrl + F5 o menu Depurar > Iniciar sin depurar
// Depurar programa: F5 o menu Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln