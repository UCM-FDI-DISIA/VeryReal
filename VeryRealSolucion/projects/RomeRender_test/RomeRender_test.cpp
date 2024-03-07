// RomeRender_test.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <RenderManager.h>
#include <Entity.h>
#include <TransformComponent.h>
#include <Camera.h>
#include <Light.h>
#include <MeshRender.h>
#include <Animator.h>
using namespace VeryReal;
int main()
{
   VeryReal::RenderManager::Instance()->InitManager("app");
   VeryReal::Entity sinbad;
   sinbad.AddComponent<TransformComponent>("CreatorTransformComponent");
   sinbad.AddComponent<MeshRender>("MeshRender", true, "modelname", "entityname", "Sinbad.mesh", VeryReal::RenderManager::Instance()->CreateNode(), VeryReal::RenderManager::Instance()->SceneManagerOgree(), VeryReal::RenderManager::Instance()->filesystemlayer_);
   sinbad.AddComponent<Light>("Light");
    while (true) {
        VeryReal::RenderManager::Instance()->Update(0.2);
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
