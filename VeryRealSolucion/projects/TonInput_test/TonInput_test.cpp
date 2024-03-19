// TonInput_test.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
#pragma once
#include <iostream>
#include "InputManager.h"
#include <SDL.h>
#undef main

int main()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* mWindow;
	mWindow = SDL_CreateWindow("Very Real", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		854, 480, SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
	SDL_Renderer* renderer = SDL_CreateRenderer(mWindow, NULL, SDL_RENDERER_SOFTWARE);

	VeryReal::InputManager::Init();
	std::cout << "Hello World!\n";
	

	while (true) {

		VeryReal::InputManager::Instance()->Refresh(); // Ih se actualiza (actua como el handleEvents())

		if (VeryReal::InputManager::Instance()->IsKeyDown(TI_SCANCODE_A)) 
			std::cout << "A" << std::endl;
        if (VeryReal::InputManager::Instance()->IsGamePadButtonDown(TI_CONTROLLER_BUTTON_A)) 
			std::cout << "BUTTON" << std::endl;
        if (VeryReal::InputManager::Instance()->GetJoystickAxisState(TI_CONTROLLER_AXIS_LEFTX) != 0) 
			std::cout << VeryReal::InputManager::Instance()->GetJoystickAxisState(TI_CONTROLLER_AXIS_LEFTX) << std::endl;
        if (VeryReal::InputManager::Instance()->GetJoystickAxisState(TI_CONTROLLER_AXIS_TRIGGERRIGHT) != 0)
                        std::cout << VeryReal::InputManager::Instance()->GetJoystickAxisState(TI_CONTROLLER_AXIS_TRIGGERRIGHT) << std::endl;
        if (VeryReal::InputManager::Instance()->GetMouseButtonState(TI_MOUSE_LEFT)) 
			std::cout << "L" << std::endl;
	}

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
