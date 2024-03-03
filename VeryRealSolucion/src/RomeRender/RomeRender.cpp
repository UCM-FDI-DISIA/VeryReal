// RomeRender.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

//#include <iostream>
//#include <OgreRoot.h>
//#include <Ogre.h>
//#include <crtdbg.h> //memory
//#include <OgreRenderSystem.h>
//#include <SDL.h>
//#undef main
//#include <stdlib.h>
#include "RenderManager.h"
#include "Window.h"
using namespace VeryReal;
int main()
{
    /*VeryReal::RenderManager::Instance()->InitManager("app");
    Window* wind = new Window();
    wind->Init();*/
   //// wind->CreateWindoww();
   // wind->demo();
   /* _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
   
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* mWindow;
    mWindow = SDL_CreateWindow("Very Real", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        854, 480, SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
    SDL_Renderer* renderer = SDL_CreateRenderer(mWindow, NULL, SDL_RENDERER_SOFTWARE);
    while (true)
    {

    }
    if (mWindow != nullptr)
    {
        SDL_DestroyWindow(mWindow);
        mWindow = nullptr;
        SDL_Quit();
    }


    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
    _CrtDumpMemoryLeaks();
    std::cout << "Hello World!\n";*/
}

// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
