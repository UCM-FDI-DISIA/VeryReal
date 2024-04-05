#pragma once
#include "VeryRealProyecto.h"/*
#include <InputManager.h>
#include <RenderManager.h>*/
#include <Window.h>
#include <chrono>
#include <Creator.h>
#include "TransformComponent.h"

const int FRAME_RATE = 3;
typedef bool(__cdecl* GameStartingPoint)();
bool VeryRealProyecto::Init() {
	
	//VeryReal::InputManager::Init();
	//VeryReal::RenderManager::Init();
	VR().CreateCreators();
	LoadGame("OgremanSolucion");


	return true;
}

void VeryRealProyecto::Loop() 
{
	uint32_t startTime, frameTime;
        startTime = (uint32_t) std::chrono::duration_cast<std::chrono::duration<float>>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
	while (true) {
        frameTime = (uint32_t) std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::high_resolution_clock::now().time_since_epoch()).count() -
            startTime;
	/*	VeryReal::InputManager::Instance()->Refresh(); */
		if (frameTime >= FRAME_RATE) {
			// Fisicas
			// Update (Componentes)
			// Render
			/*VeryReal::RenderManager::Instance()->Update(frameTime);*/
			// Sonido
			std::cout << frameTime << std::endl;
            startTime = (uint32_t) std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
		}
	}
}

void VeryRealProyecto::Delete() 
{
	//if (mWindow != nullptr)
	//{
	//	SDL_DestroyWindow(mWindow);
	//	mWindow = nullptr;
	//	SDL_Quit();
	//}

}
void VeryRealProyecto::CreateCreators() {
	//VeryReal::CreatorTransformComponent* t = new VeryReal::CreatorTransformComponent();
	//VeryReal::Creator::Instance()->AddCreator("transform", new VeryReal::CreatorTransformComponent());
}

bool VeryRealProyecto::LoadGame(std::string gameName)
{
	//Tengo que hacer cambios a gameName para que este sea la ruta al juego. Puede ser relativa ya que siempre sabemos donde va a estar el juego.
    gameName = "./" + gameName + ".dll";
	std::wstring wideGameName = std::wstring(gameName.begin(), gameName.end());
	gameDll = LoadLibrary(wideGameName.c_str());


	if(gameDll != NULL)
	{
		std::cout << "Juego cargado correctamente";
		GameStartingPoint entryPoint =
			(GameStartingPoint)GetProcAddress(gameDll, "start");
		if (entryPoint != NULL) {
			return entryPoint();
		}
	}
	else
	{
		std::cout << "El juego no existe";
		return false;
	}
	return true;
}
// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
