#pragma once
#include <iostream>
#include <SDL.h>
#include "InputManager.h"
#include "Singleton.h"

using namespace std;

void VeryReal::InputManager::InitManager() {   // Flags de sdl necesarias para el input de teclas y mando
    kb_state = SDL_GetKeyboardState(0);
    ClearState(true);
    if (!SDL_WasInit(SDL_INIT_EVENTS)) 
        SDL_Init(SDL_INIT_EVENTS);
    if (!SDL_WasInit(SDL_INIT_JOYSTICK)) 
        SDL_Init(SDL_INIT_JOYSTICK);
    if (!SDL_WasInit(SDL_INIT_GAMECONTROLLER)) 
        SDL_Init(SDL_INIT_GAMECONTROLLER);
}

void VeryReal::InputManager::ClearState(bool clearMouseButtons) {
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

void VeryReal::InputManager::Update(const SDL_Event& event) {
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

void VeryReal::InputManager::Refresh() {
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

void VeryReal::InputManager::OnMouseButtonChange(const SDL_Event& event, bool isDown) {
    is_mouse_button_event = true;
    switch (event.button.button) {
    case SDL_BUTTON_LEFT : mb_state [TI_MOUSE_LEFT] = isDown; break;
    case SDL_BUTTON_MIDDLE : mb_state [TI_MOUSE_MIDDLE] = isDown; break;
    case SDL_BUTTON_RIGHT : mb_state [TI_MOUSE_RIGHT] = isDown; break;
    default : break;
    }
}

void VeryReal::InputManager::HandleWindowEvent(const SDL_Event& event) {
    switch (event.window.event) {
    case SDL_WINDOWEVENT_CLOSE : is_close_window_event = true; break;
    default : break;
    }
}

void VeryReal::InputManager::OnMouseMotion(const SDL_Event& event) {
    is_mouse_motion_event = true;
    mouse_pos.first = event.motion.x;
    mouse_pos.second = event.motion.y;
}

bool VeryReal::InputManager::IsGamePadButtonDown(TI_GameControllerButton button) {
    if (is_game_controller_connected) {
        if (SDL_GameControllerGetButton(controller, (SDL_GameControllerButton)button)) {
            return true;
        }
    }
    return false;
}

float VeryReal::InputManager::GetJoystickAxisState(TI_GameControllerAxis axis) {
    if (is_game_controller_connected) {
        float axisState = SDL_GameControllerGetAxis(controller, (SDL_GameControllerAxis)axis) / 32767.0f;
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