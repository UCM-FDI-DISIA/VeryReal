#pragma once
#include "VeryRealProyecto.h"
#include <InputManager.h>
#include <RenderManager.h>
#include <PhysicsManager.h>
#include <AudioLeon.h>
#include <LuaLuengo.h>
#include "SceneManager.h"
#include <Window.h>
#include <chrono>
#include <Creator.h>
#include "ComponentesAudio/AudioListenerComponent.h"
#include "ComponentesAudio/AudioSourceComponent.h"
#include "CreatorTransformComponent.h"
#include "CreatorRigidBodyComponent.h"
#include "CreatorColliderComponent.h"
#include "CreatorMeshRenderComponent.h"
#include "CreatorLightComponent.h"
#include "CreatorCameraComponent.h"
#include "CreatorAnimatorComponent.h"
#include "CreatorTransformComponent.h"


const double FRAME_RATE = 0.01;
typedef bool(__cdecl* GameStartingPoint)();
typedef bool(__cdecl* Prueba)();

typedef bool(__cdecl* Start)();

bool VeryRealProyecto::Init() {
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    VeryReal::InputManager::Instance()->Init();
	//VeryReal::RenderManager::Init();
	VR().CreateCreators();
	LoadGame("OgremanSolucion");
    Start startFunction = (Start)GetProcAddress(gameDll, "start");
    if (startFunction != NULL) {
        startFunction();
    }
    else
        return false;
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
            VeryReal::PhysicsManager::Instance()->Update(frameTime);	
            VeryReal::SceneManager::Instance()->Update(frameTime);
            VeryReal::RenderManager::Instance()->Update(frameTime);
            VeryReal::AudioLeon::Instance()->Update(frameTime);
			std::cout << frameTime << std::endl;
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
}

void VeryRealProyecto::CreateCreators() 
{
	//FALTAN LOS DOS DE SONIDO

	VeryReal::Creator::Instance()->AddCreator("TransformComponent", new VeryReal::CreatorTransformComponent());
	VeryReal::Creator::Instance()->AddCreator("rigidbody", new VeryReal::CreatorRigidBodyComponent());
	VeryReal::Creator::Instance()->AddCreator("collider", new VeryReal::CreatorColliderComponent());
	VeryReal::Creator::Instance()->AddCreator("meshrender", new VeryReal::CreatorMeshRenderComponent());
	VeryReal::Creator::Instance()->AddCreator("light", new VeryReal::CreatorLightComponent());
	VeryReal::Creator::Instance()->AddCreator("camera", new VeryReal::CreatorCameraComponent());
	VeryReal::Creator::Instance()->AddCreator("animator", new VeryReal::CreatorAnimatorComponent());
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

	if(gameDll != NULL) {
		std::cout << "Juego cargado correctamente";
		Prueba entryPoint = (Prueba)GetProcAddress(gameDll, "main");
		if (entryPoint != NULL) {
			return entryPoint();
		}
	}
	else {
		std::cout << "El juego no existe";
		return false;
	}
    FreeLibrary(gameDll);
	return true;
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