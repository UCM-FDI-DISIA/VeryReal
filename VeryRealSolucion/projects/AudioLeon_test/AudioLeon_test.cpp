// AudioLeon_test.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <AudioLeon.h>
#include "Creator.h"
#include "../AudioLeon/CreatorAudioSourceComponent.h"
#include "../AudioLeon/CreatorAudioListenerComponent.h"
#include "CreatorTransformComponent.h"
#include "../PedroBullet/CreatorRigidBodyComponent.h"
#include "Entity.h"
#include "Component.h"
#include "Scene.h"
#include "SceneManager.h"

using namespace std;
using namespace VeryReal;

int main() {
    int t = 0;
    bool Play = false;
    VeryReal::Creator::Init();
    VeryReal::SceneManager::Init();
    VeryReal::AudioLeon::Init();
    VeryReal::AL().InitManager();

    VeryReal::Creator::Instance()->AddCreator("TransformComponent", new VeryReal::CreatorTransformComponent());
    Creator::Instance()->GetCreator("TransformComponent")->AddParameter("a", 0);
    Creator::Instance()->GetCreator("TransformComponent")->AddParameter("position", Vector3{0, 0, 20});
    Creator::Instance()->GetCreator("TransformComponent")->AddParameter("rotation", Vector3{0, 0, 0});
    Creator::Instance()->GetCreator("TransformComponent")->AddParameter("scale", Vector3{1, 1, 1});

    //int shapeType, float mass, float friction, float restitution, int movementType, bool trigger
    VeryReal::Creator::Instance()->AddCreator("RigidBodyComponent", new VeryReal::CreatorRigidBodyComponent());
    Creator::Instance()->GetCreator("RigidBodyComponent")->AddParameter("shapeType", 1);
    Creator::Instance()->GetCreator("RigidBodyComponent")->AddParameter("mass", float(1));
    Creator::Instance()->GetCreator("RigidBodyComponent")->AddParameter("friction", float(0));
    Creator::Instance()->GetCreator("RigidBodyComponent")->AddParameter("restitution", float(0));
    Creator::Instance()->GetCreator("RigidBodyComponent")->AddParameter("movementType", int(0));
    Creator::Instance()->GetCreator("RigidBodyComponent")->AddParameter("trigger", true);

    #pragma region audiosource
    VeryReal::Creator::Instance()->AddCreator("AudioSourceComponent", new VeryReal::CreatorAudioSourceComponent());
    Creator::Instance()->GetCreator("AudioSourceComponent")->AddParameter("name", std::string("sonido"));
    Creator::Instance()->GetCreator("AudioSourceComponent")->AddParameter("path", std::string("musicaCircuito.mp3"));
    Creator::Instance()->GetCreator("AudioSourceComponent")->AddParameter("groupchannel", std::string("master"));
    Creator::Instance()->GetCreator("AudioSourceComponent")->AddParameter("onstart", true);
    Creator::Instance()->GetCreator("AudioSourceComponent")->AddParameter("loop", true);
    Creator::Instance()->GetCreator("AudioSourceComponent")->AddParameter("threed", true);
    Creator::Instance()->GetCreator("AudioSourceComponent")->AddParameter("volume", 1);
    Creator::Instance()->GetCreator("AudioSourceComponent")->AddParameter("mindistance", 0.0f);
    Creator::Instance()->GetCreator("AudioSourceComponent")->AddParameter("maxdistance", 100000.0f);
#pragma endregion
#pragma region audiolistener
    VeryReal::Creator::Instance()->AddCreator("AudioListenerComponent", new VeryReal::CreatorAudioListenerComponent());
#pragma endregion


     VeryReal::Scene* s = SceneManager::Instance()->AddScene("Play", true);
    s = SceneManager::Instance()->GetScene("Play");
    Entity* e = s->AddEntity("Player");
    Component* transform = e->AddComponent("TransformComponent");
    Component* rigid = e->AddComponent("RigidBodyComponent");
    Component* source = e->AddComponent("AudioSourceComponent");
    Component* listen = e->AddComponent("AudioListenerComponent");

    while ((true)) {
        VeryReal::AL().SystemRefresh(t);
        if (!Play) {
            //VeryReal::AL().AudioSourceListenerTest();
            std::cout << "pillado";
            s->Update(0.1);
            Play = true;
        }
        //cout << "PRUEBA " << VeryReal::AL().InputSoundIntensity() << endl;
        ++t;

    }
    std::cout << "Hello World!\n";
    return 0;
}

// Ejecutar programa: Ctrl + F5 o menu Depurar > Iniciar sin depurar
// Depurar programa: F5 o menu Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
