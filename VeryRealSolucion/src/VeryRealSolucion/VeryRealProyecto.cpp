#pragma once
#include "VeryRealProyecto.h"
#include <Window.h>
#include <chrono>
#include <thread>
#include <filesystem>


#pragma region LUA LUENGOº
//creators de Lua:
#include "SceneManager.h"
#include "ScriptManager.h"
#pragma endregion
#pragma region AUDIO LEON
#include <AudioManager.h>
//creators de Audio:
#include "CreatorAudioSourceComponent.h"
#include "CreatorAudioListenerComponent.h"
#pragma endregion
#pragma region TONINPUT
#include <InputManager.h>
#pragma endregion
#pragma region GUILLERMO EL ARQUITECTO
#include <Creator.h>
#include "CreatorTransformComponent.h"
#include <ErrorInformant.h>
#include <ErrorManager.h>
#pragma endregion
#pragma region PEDROBULLET
#include <PhysicsManager.h>
//creators de Fisica:
#include "CreatorRigidBodyComponent.h"
#include "CreatorColliderComponent.h"
#pragma endregion
#pragma region ROMERENDER
#include <RenderManager.h>
//creators de UI Render:
#include "UI/CreatorUIButtonComponent.h"
#include "UI/CreatorUIProgressBarComponent.h"
#include "UI/CreatorUISpriteRenderComponent.h"
#include "UI/CreatorUITextComponent.h"
#include "UI/CreatorUITransformComponent.h"
//creators de Render:
#include "CreatorAnimatorComponent.h"
#include "CreatorCameraComponent.h"
#include "CreatorLightComponent.h"
#include "CreatorMeshRenderComponent.h"
#include "CreatorSmokeEffect.h"
#pragma endregion


const float FRAME_RATE = 1.0f / 60.0f;
const float FIXED_UPDATE_RATE = 1.0f / 50.0f;
typedef bool(__cdecl* GameStartingPoint)();
typedef bool(__cdecl* Prueba)();
typedef std::pair<bool, std::string>(__cdecl* Start)();
typedef void(__cdecl* MainLoop)(float dt);
using namespace VeryReal;
using namespace std;
using SetUpMessage = std::pair<bool, std::string>;
SetUpMessage VeryRealProyecto::InitVeryReal() {
    auto initPointers = InitPointers();
    if (!initPointers.first) {
        this->managerInitializeError = true;
        return initPointers;
    }

    CreateCreators();

    std::string dllName = "Game";

    auto loadGame = LoadGame(dllName);
    if (!loadGame.first) {
        return loadGame;
    }
  
    return {true, "The engine is ready to start the game!"};
}

SetUpMessage VeryRealProyecto::InitPointers() {
    // Para cada manager comprobamos los errores de inicializacion

    SetUpMessage ErrorInformantmessage = VeryReal::ErrorInformant::Init();
    if (!ErrorInformantmessage.first) {
        return ErrorInformantmessage;
    }
    SetUpMessage creatorMessage = VeryReal::Creator::Init();
    if (!creatorMessage.first) {

        return creatorMessage;
    }

    SetUpMessage inputManagerMessage = VeryReal::InputManager::Init();
    if (!inputManagerMessage.first) {

        delete VeryReal::Creator::Instance();
        return inputManagerMessage;
    }

    SetUpMessage renderManagerMessage = VeryReal::RenderManager::Init();
    if (!renderManagerMessage.first) {


        delete VeryReal::InputManager::Instance();
        delete VeryReal::Creator::Instance();
        return renderManagerMessage;
    }

    SetUpMessage audioManagerMessage = VeryReal::AudioManager::Init();
    if (!audioManagerMessage.first) {


        delete VeryReal::RenderManager::Instance();
        delete VeryReal::InputManager::Instance();
        delete VeryReal::Creator::Instance();
        return audioManagerMessage;
    }

    SetUpMessage scriptManagerMessage = VeryReal::ScriptManager::Init();
    if (!scriptManagerMessage.first) {


        delete VeryReal::RenderManager::Instance();
        delete VeryReal::InputManager::Instance();
        delete VeryReal::Creator::Instance();
        return scriptManagerMessage;
    }

    SetUpMessage physicManagerMessage = VeryReal::PhysicsManager::Init();
    if (!physicManagerMessage.first) {
        delete VeryReal::ScriptManager::Instance();
        delete VeryReal::RenderManager::Instance();
        delete VeryReal::InputManager::Instance();
        delete VeryReal::Creator::Instance();
        return physicManagerMessage;
    }

    SetUpMessage sceneManagerMessage = VeryReal::SceneManager::Init();
    if (!sceneManagerMessage.first) {

        delete VeryReal::PhysicsManager::Instance();
        delete VeryReal::ScriptManager::Instance();
        delete VeryReal::RenderManager::Instance();
        delete VeryReal::InputManager::Instance();
        delete VeryReal::Creator::Instance();
        return sceneManagerMessage;
    }

    SetUpMessage errorManagerMessage = VeryReal::ErrorManager::Init();
    if (!errorManagerMessage.first) {

        delete VeryReal::SceneManager::Instance();
        delete VeryReal::PhysicsManager::Instance();
        delete VeryReal::ScriptManager::Instance();
        delete VeryReal::RenderManager::Instance();
        delete VeryReal::InputManager::Instance();
        delete VeryReal::Creator::Instance();
        return errorManagerMessage;
    }

    

    return {true, "Managers pointers where succesfully created"};
}
void VeryRealProyecto::CreateCreators() {
    VeryReal::Creator::Instance()->AddCreator("TransformComponent", new VeryReal::CreatorTransformComponent());
    VeryReal::Creator::Instance()->AddCreator("RigidBodyComponent", new VeryReal::CreatorRigidBodyComponent());
    VeryReal::Creator::Instance()->AddCreator("ColliderComponent", new VeryReal::CreatorColliderComponent());
    VeryReal::Creator::Instance()->AddCreator("MeshRenderComponent", new VeryReal::CreatorMeshRenderComponent());
    VeryReal::Creator::Instance()->AddCreator("LightComponent", new VeryReal::CreatorLightComponent());
    VeryReal::Creator::Instance()->AddCreator("CameraComponent", new VeryReal::CreatorCameraComponent());
    VeryReal::Creator::Instance()->AddCreator("AnimatorComponent", new VeryReal::CreatorAnimatorComponent());
    VeryReal::Creator::Instance()->AddCreator("AudioSourceComponent", new VeryReal::CreatorAudioSourceComponent());
    VeryReal::Creator::Instance()->AddCreator("AudioListenerComponent", new VeryReal::CreatorAudioListenerComponent());
    VeryReal::Creator::Instance()->AddCreator("UITransformComponent", new VeryReal::CreatorUITransformComponent());
    VeryReal::Creator::Instance()->AddCreator("UITextComponent", new VeryReal::CreatorUITextComponent());
    VeryReal::Creator::Instance()->AddCreator("UISpriteRendererComponent", new VeryReal::CreatorUISpriteRenderComponent());
    VeryReal::Creator::Instance()->AddCreator("UIButtonComponent", new VeryReal::CreatorButtonComponent());
    VeryReal::Creator::Instance()->AddCreator("UIProgressBarComponent", new VeryReal::CreatorUIProgressBarComponent());
    VeryReal::Creator::Instance()->AddCreator("SmokeEffect", new VeryReal::CreatorSmokeEffect());
}

SetUpMessage VeryRealProyecto::LoadGame(std::string gameName) {
    //Tengo que hacer cambios a gameName para que este sea la ruta al juego. Puede ser relativa ya que siempre sabemos donde va a estar el juego.
#ifdef _DEBUG
    gameName = "./" + gameName + "_d.dll";
#endif   // DEBUG

#ifdef NDEBUG
    gameName = "./" + gameName + ".dll";
#endif   // NDEBUG

    std::wstring wideGameName = std::wstring(gameName.begin(), gameName.end());
    gameDll = LoadLibrary(wideGameName.c_str());

    if (gameDll != NULL) {
        std::cout << "Juego cargado correctamente";
        Start startFunction = (Start)GetProcAddress(gameDll, "start");

        if (startFunction != NULL) {
            std::pair<bool, std::string> inicioJuego = startFunction();
            if (!inicioJuego.first) return inicioJuego;
        }
    }
    else {
        return {false, "El juego no existe"};
    }
    return {true, "Game was loaded!"};
}
void VeryRealProyecto::Loop() {

    auto startTime = std::chrono::high_resolution_clock::now();
    auto previousTime = startTime;
    auto previousFixedUpdateTime = startTime;

    while (!VeryReal::InputManager::Instance()->getQuit() && VeryReal::ErrorManager::Instance()->getError().first) {
        
        auto currentTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> elapsedTime = currentTime - previousTime;
        std::chrono::duration<float> fixedUpdateElapsedTime = currentTime - previousFixedUpdateTime;
        float frameTime = elapsedTime.count();

        VeryReal::InputManager::Instance()->Refresh();

         while (fixedUpdateElapsedTime.count() >= FIXED_UPDATE_RATE) {
            VeryReal::PhysicsManager::Instance()->FixedUpdate(FIXED_UPDATE_RATE);   // Función de FixedUpdate
             fixedUpdateElapsedTime -= std::chrono::duration<float>(FIXED_UPDATE_RATE);
            previousFixedUpdateTime += std::chrono::duration_cast<std::chrono::steady_clock::duration>(std::chrono::duration<float>(FIXED_UPDATE_RATE));
         }

        if (frameTime >= FRAME_RATE) {
            VeryReal::PhysicsManager::Instance()->Update(frameTime);
            VeryReal::SceneManager::Instance()->Update(frameTime);
            VeryReal::RenderManager::Instance()->Update(frameTime);
            VeryReal::AudioManager::Instance()->Update(frameTime);
            previousTime = currentTime;
        }
        else {
            auto sleepDuration = std::chrono::duration<float>(FRAME_RATE - frameTime);
            std::this_thread::sleep_for(sleepDuration);
        }
    }
}

void VeryRealProyecto::Delete() {
    delete (VeryReal::SceneManager::Instance());
    delete (VeryReal::ScriptManager::Instance());

    delete (VeryReal::AudioManager::Instance());
    delete (VeryReal::Creator::Instance());
    delete (VeryReal::InputManager::Instance());
    delete (VeryReal::PhysicsManager::Instance());
    delete (VeryReal::RenderManager::Instance());
    delete (VeryReal::ErrorManager::Instance());

    FreeLibrary(gameDll);
}

// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos:
//   1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln