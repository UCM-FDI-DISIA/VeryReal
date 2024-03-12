// RomeRender.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.

#include <iostream>
#include <SDL.h>
#include "TonInput.h"
using namespace std;

void TonInput::ClearState(bool clearMouseButtons){
    is_close_window_event = false;
    is_key_down_event = false;
    is_key_up_event = false;
    is_mouse_button_event = false;
    is_mouse_motion_event = false;
    if (clearMouseButtons) {
        for (auto i = 0u; i < 3; i++) {
            mb_state[i] = false;
        }
    }
}

void TonInput::Update(const SDL_Event& event) {
    switch (event.type) {
    case SDL_KEYDOWN:
        OnKeyDown(event);
        break;
    case SDL_KEYUP:
        OnKeyUp(event);
        break;
    case SDL_MOUSEMOTION:
        OnMouseMotion(event);
        break;
    case SDL_MOUSEBUTTONDOWN:
        OnMouseButtonChange(event, true);
        break;
    case SDL_MOUSEBUTTONUP:
        OnMouseButtonChange(event, false);
        break;
    case SDL_WINDOWEVENT:
        HandleWindowEvent(event);
        break;
    case SDL_QUIT:
        is_quit = true;
    default:
        break;
    }
}

void TonInput::Refresh() {
    SDL_Event event;
    ClearState();

    if (SDL_NumJoysticks() < 1) { // No hay mandos conectados
        if (is_game_controller_connected) {
            SDL_GameControllerClose(controller);
            is_game_controller_connected = false;
        }
    }
    else { // Se detecta un mando
        if (!is_game_controller_connected) {
            controller = SDL_GameControllerOpen(0);
            if (SDL_IsGameController(0))
                is_game_controller_connected = true;
        }
    }

    while (SDL_PollEvent(&event))
        Update(event);
}

bool TonInput::IsGamePadButtonDown(TI_GameControllerButton button) {
    if (is_game_controller_connected) {
        if (SDL_GameControllerGetButton(controller, (SDL_GameControllerButton)button)) {
            return true;
        }
    }
    return false;
}

float TonInput::GetJoystickAxisState(TI_GameControllerAxis axis) {
    if (is_game_controller_connected) {
        float axisState = SDL_GameControllerGetAxis(controller, (SDL_GameControllerAxis)axis) / 32767.0;
        if (abs(axisState) > 1) axisState = round(axisState); // Corrección (los negativos llegan hasta -32768 y los positivos hasta 32767)
        else if (abs(axisState) < joystick_death_zone) axisState = 0;
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