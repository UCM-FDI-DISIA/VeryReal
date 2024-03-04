#include <TonInput.h>
#include <RenderManager.h>
#include <Window.h>
// VeryRealProyecto.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//


//Submodulos de Github
//Los juegos, descargan consigo el motor.
//Desde el motor siempre sabemos donde esta la dll del juego.
//dll export es una manera de que desde el juego, esa función sea visible.



#include <iostream>

const int FRAME_RATE = 3;

bool Init() {

	SDL_Init(SDL_INIT_EVERYTHING); // RomeRender y TonInput necesitan inicir SDL 
	//SDL_Window* mWindow; // Ventana (temporal) para que funcione el input
	//mWindow = SDL_CreateWindow("Very Real", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
	//	854, 480, SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
	////SDL_Renderer* renderer = SDL_CreateRenderer(mWindow, NULL, SDL_RENDERER_SOFTWARE);
	//VeryReal::RenderManager().Instance()->InitManager("app"); //InitManager
	TI().Init();
}

void Loop() {

	uint32_t startTime, frameTime;
	startTime = SDL_GetTicks();
	while (true) {
		frameTime = SDL_GetTicks() - startTime;
		TI().Refresh(); // Ih se actualiza (actua como el handleEvents())
		if (frameTime >= FRAME_RATE) {
			// Fisicas
			// Update (Componentes)
			// Render
			// Sonido
			cout << frameTime << endl;
			startTime = SDL_GetTicks();
		}
	}

}

void Exit() {
	//if (mWindow != nullptr)
	//{
	//	SDL_DestroyWindow(mWindow);
	//	mWindow = nullptr;
	//	SDL_Quit();
	//}

}


// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
