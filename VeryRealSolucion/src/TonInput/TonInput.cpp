// RomeRender.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <crtdbg.h> //memory
#include <SDL.h>
#undef main
#include <stdlib.h>
#include "InputHandler.h"
using namespace std;
int main()
{
	const int FRAME_RATE = 3;
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* mWindow;
    mWindow = SDL_CreateWindow("Very Real", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        854, 480, SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
    SDL_Renderer* renderer = SDL_CreateRenderer(mWindow, NULL, SDL_RENDERER_SOFTWARE);
    
	uint32_t startTime, frameTime;
	startTime = SDL_GetTicks();
	while (true) {
		frameTime = SDL_GetTicks() - startTime;
		ih().refresh(); // Ih se actualiza (actua como el handleEvents())
		if (frameTime >= FRAME_RATE) {
			
			if (ih().isKeyDown(SDL_SCANCODE_X))
				cout << "X" << endl;

			if (ih().isGamePadButtonDown(SDL_CONTROLLER_BUTTON_X))
				cout << "boton1" << endl;
			if (ih().isGamePadButtonDown(SDL_CONTROLLER_BUTTON_A))
				cout << "boton2" << endl;
			if (ih().isGamePadButtonDown(SDL_CONTROLLER_BUTTON_B))
				cout << "boton3" << endl;

			if (ih().getJoystickAxisState(SDL_CONTROLLER_AXIS_LEFTX) != 0)
				cout << ih().getJoystickAxisState(SDL_CONTROLLER_AXIS_LEFTX) << endl;
			if (ih().getJoystickAxisState(SDL_CONTROLLER_AXIS_RIGHTY) != 0)
				cout << ih().getJoystickAxisState(SDL_CONTROLLER_AXIS_RIGHTY) << endl;

			if (ih().getJoystickAxisState(SDL_CONTROLLER_AXIS_TRIGGERLEFT) != 0)
				cout << ih().getJoystickAxisState(SDL_CONTROLLER_AXIS_TRIGGERLEFT) << endl;

			startTime = SDL_GetTicks();
		}
	}

    if (mWindow != nullptr)
    {
        SDL_DestroyWindow(mWindow);
        mWindow = nullptr;
        SDL_Quit();
    }


    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
    _CrtDumpMemoryLeaks();
    std::cout << "Hello World!\n";
}

// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
