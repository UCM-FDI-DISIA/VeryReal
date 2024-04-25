#pragma once
#include "VeryRealProyecto.h"
#include <InputManager.h>
#include <RenderManager.h>
#include <PhysicsManager.h>
#include <AudioLeon.h>
#include <LuaLuengo.h>
#include "SceneManager.h"
#include "ScriptManager.h"
#include <Window.h>
#include <chrono>
#include <Creator.h>
#include "ComponentesAudio/AudioListenerComponent.h"
#include "ComponentesAudio/AudioSourceComponent.h"
#include "ComponentesAudio/CreatorAudioSourceComponent.h"
#include "ComponentesAudio/CreatorAudioListenerComponent.h"
#include "CreatorTransformComponent.h"
#include "CreatorRigidBodyComponent.h"
#include "CreatorColliderComponent.h"
#include "CreatorMeshRenderComponent.h"
#include "CreatorLightComponent.h"
#include "CreatorCameraComponent.h"
#include "CreatorAnimatorComponent.h"
#include "CreatorTransformComponent.h"
#include "UI/CreatorUITransformComponent.h"
#include "UI/CreatorUITextComponent.h"
#include "UI/CreatorUIButtonComponent.h"
#include "UI/CreatorUIProgressBarComponent.h"
#include <filesystem>
const double FRAME_RATE = 0.01;
typedef bool(__cdecl* GameStartingPoint)();
typedef bool(__cdecl* Prueba)();
typedef bool(__cdecl* Start)();
typedef void(__cdecl* MainLoop)();
using namespace VeryReal;
bool VeryRealProyecto::InitVeryReal() {
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	if (!InitPointers()) return false;
    if (!InitManagers()) return false;
    if (!CreateCreators()) return false;

	std::string dllName = "Game"; 
	if (!LoadGame(dllName)) return false;
    gameLoop  = (MainLoop)GetProcAddress(gameDll, "loop");
    if (gameLoop == NULL) return false;    
	return true;
}
bool VeryRealProyecto::InitPointers() {
        if (!VeryReal::InputManager::Init() || !VeryReal::RenderManager::Init() || !VeryReal::AudioLeon::Init() 
			|| !VeryReal::ScriptManager::Init() ||!VeryReal::PhysicsManager::Init()||!VeryReal::SceneManager::Init())return false;
        return true;
       
}
bool VeryRealProyecto::InitManagers(){ 
	VeryReal::InputManager::Instance()->InitManager();
    VeryReal::RenderManager::Instance()->InitManager("JUEGO");
	VeryReal::AudioLeon::Instance()->InitManager();
    VeryReal::PhysicsManager::Instance()->InitManager();
    VeryReal::ScriptManager::Instance()->InitManager();
    return true;
    
}
bool VeryRealProyecto::CreateCreators() {
    //FALTAN LOS DOS DE SONIDO
    VeryReal::Creator::Init();
    VeryReal::Creator::Instance()->AddCreator("TransformComponent", new VeryReal::CreatorTransformComponent());
    VeryReal::Creator::Instance()->AddCreator("rigidbody", new VeryReal::CreatorRigidBodyComponent());
    VeryReal::Creator::Instance()->AddCreator("collider", new VeryReal::CreatorColliderComponent());
    VeryReal::Creator::Instance()->AddCreator("MeshRenderComponent", new VeryReal::CreatorMeshRenderComponent());
    VeryReal::Creator::Instance()->AddCreator("LightComponent", new VeryReal::CreatorLightComponent());
    VeryReal::Creator::Instance()->AddCreator("CameraComponent", new VeryReal::CreatorCameraComponent());
    VeryReal::Creator::Instance()->AddCreator("animator", new VeryReal::CreatorAnimatorComponent());
    VeryReal::Creator::Instance()->AddCreator("AudioSourceComponent", new VeryReal::CreatorAudioSourceComponent());
    VeryReal::Creator::Instance()->AddCreator("AudioListenerComponent", new VeryReal::CreatorAudioListenerComponent());
    VeryReal::Creator::Instance()->AddCreator("UITransformComponent", new VeryReal::CreatorUITransformComponent());
    VeryReal::Creator::Instance()->AddCreator("UITextComponent", new VeryReal::CreatorUITextComponent());
    VeryReal::Creator::Instance()->AddCreator("UIButtonComponent", new VeryReal::CreatorButtonComponent());
    VeryReal::Creator::Instance()->AddCreator("UIProgressBarComponent", new VeryReal::CreatorUIProgressBarComponent());
    return true;
}
bool VeryRealProyecto::LoadGame(std::string gameName) {
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
            return startFunction();
        }
    }
    else {
        std::cout << "El juego no existe";

        return false;
    }
    return true;
}
void VeryRealProyecto::Loop() {
    
	float startTime, frameTime;
    startTime = std::chrono::duration_cast<std::chrono::duration<float>>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
    while (!VeryReal::InputManager::Instance()->getQuit())
		{
        frameTime = (float) std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::high_resolution_clock::now().time_since_epoch()).count() - startTime;
		VeryReal::InputManager::Instance()->Refresh(); 
		if (frameTime >= FRAME_RATE) {
        
            gameLoop();   
            VeryReal::PhysicsManager::Instance()->Update(frameTime);	
            VeryReal::SceneManager::Instance()->Update(frameTime);
            VeryReal::RenderManager::Instance()->Update(frameTime);
            VeryReal::AudioLeon::Instance()->Update(frameTime);
            startTime = (float) std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
		}
	}
}
void VeryRealProyecto::Delete() {
	//if (mWindow != nullptr) {
	//	SDL_DestroyWindow(mWindow);
	//	mWindow = nullptr;
	//	SDL_Quit();
	//}
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