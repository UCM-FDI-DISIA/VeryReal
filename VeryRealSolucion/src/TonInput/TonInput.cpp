// RomeRender.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.

#include <iostream>
#include <crtdbg.h> //memory
#include <SDL.h>
#undef main
#include <stdlib.h>
#include <TonInput.h>
using namespace std;


void TonInput::clearState(bool clearMouseButtons)
{
    isCloseWindoEvent_ = false;
    isKeyDownEvent_ = false;
    isKeyUpEvent_ = false;
    isMouseButtonEvent_ = false;
    isMouseMotionEvent_ = false;
    if (clearMouseButtons) {
        for (auto i = 0u; i < 3; i++) {
            mbState_[i] = false;
        }
    }
}

void TonInput::update(const SDL_Event& event)
{
    switch (event.type) {
    case SDL_KEYDOWN:
        onKeyDown(event);
        break;
    case SDL_KEYUP:
        onKeyUp(event);
        break;
    case SDL_MOUSEMOTION:
        onMouseMotion(event);
        break;
    case SDL_MOUSEBUTTONDOWN:
        onMouseButtonChange(event, true);
        break;
    case SDL_MOUSEBUTTONUP:
        onMouseButtonChange(event, false);
        break;
    case SDL_WINDOWEVENT:
        handleWindowEvent(event);
        break;
    case SDL_QUIT:
        isQuit = true;
    default:
        break;
    }
}

void TonInput::refresh() 
{
    SDL_Event event;
    clearState();

    if (SDL_NumJoysticks() < 1) { // No hay mandos conectados
        if (isGameControllerConected_) {
            SDL_GameControllerClose(controller_);
            isGameControllerConected_ = false;
        }
    }
    else { // Se detecta un mando
        if (!isGameControllerConected_) {
            controller_ = SDL_GameControllerOpen(0);
            if (SDL_IsGameController(0))
                isGameControllerConected_ = true;
        }
    }

    while (SDL_PollEvent(&event))
        update(event);
}

bool TonInput::isGamePadButtonDown(SDL_GameControllerButton button) 
{
    if (isGameControllerConected_) {
        if (SDL_GameControllerGetButton(controller_, button)) {
            return true;
        }
    }
    return false;
}

float TonInput:: getJoystickAxisState(SDL_GameControllerAxis axis) 
{
    if (isGameControllerConected_) {
        float axisState = SDL_GameControllerGetAxis(controller_, axis) / 32767.0;
        if (abs(axisState) > 1) axisState = round(axisState); // Corrección (los negativos llegan hasta -32768 y los positivos hasta 32767)
        else if (abs(axisState) < joystickDeathZone_) axisState = 0;
        return (axisState);
    }
    return 0; // Valor predeterminado si el joystick no está conectado o el eje no se está utilizando
}


// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
