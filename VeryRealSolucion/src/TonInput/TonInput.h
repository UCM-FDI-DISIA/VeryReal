#ifndef TONINPUT
#define TONINPUT
#pragma once

#include <vector>
#include "Singleton.h"
#include <Manager.h>
#include <array>
#include <SDL.h>
#include "TonMapeo.h"

using namespace std;

class TonInput : public VeryReal::Manager<TonInput> {
    friend Singleton<TonInput>;

public:
    virtual ~TonInput() {}

    /// Limpia el estado de la entrada
    void ClearState(bool clearMouseButtons = false);

    /// Actualiza el estado de la entrada con un nuevo evento
    void Update(const SDL_Event& event);

    /// Refresca el estado de entrada del teclado, controlador y raton
    void Refresh();

    /// Comprueba si ha ocurrido un evento de cierre de ventana
    /// @return True si ha ocurrido un evento de cierre de ventana, false en caso contrario
    inline bool CloseWindowEvent() {
        return is_close_window_event;
    }

    // METODOS DE TECLADO

    /// Comprueba si ha ocurrido un evento de tecla presionada
    /// @return True si ha ocurrido un evento de tecla presionada, false en caso contrario
    inline bool KeyDownEvent() {
        return is_key_down_event;
    }

    /// Comprueba si ha ocurrido un evento de tecla liberada
    /// @return True si ha ocurrido un evento de tecla liberada, false en caso contrario
    inline bool KeyUpEvent() {
        return is_key_up_event;
    }

    /// Comprueba si una tecla especifica esta presionada actualmente
    /// @param key -> El SDL_Scancode de la tecla a comprobar
    inline bool IsKeyDown(TI_KeyCode key) {
        return kb_state[key] == 1;
    }

    /// Comprueba si una tecla especifica esta liberada actualmente
    /// @param key -> El SDL_Scancode de la tecla a comprobar
    inline bool IsKeyUp(TI_KeyCode key) {
        return kb_state[key] == 0;
    }


    // METODOS DE RATON

    /// Comprueba si el raton esta recibiendo algun evento de movimiento
    /// @return True si el raton esta recibiendo algun evento de movimiento, false en caso contrario
    inline bool MouseMotionEvent() {
        return is_mouse_motion_event;
    }

    /// Comprueba si se ha activado el evento "quit"
    /// @return True si se ha activado el evento "quit", false en caso contrario
    inline bool Quit() {
        return is_quit;
    }

    /// Comprueba si el raton esta recibiendo algun evento de boton
    /// @return True si el raton esta recibiendo algun evento de boton, false en caso contrario
    inline bool MouseButtonEvent() {
        return is_mouse_button_event;
    }

    /// Comprueba la posicion del raton
    /// @return Un par que contiene las coordenadas x e y de la posicion del raton
    inline const std::pair<Sint32, Sint32>& GetMousePos() {
        return mouse_pos;
    }

    /// Comprueba el estado de un boton especifico del raton
    /// @param button -> El boton del raton a comprobar
    /// @return El estado del boton del raton especificado
    inline int GetMouseButtonState(TI_MouseButton button) {
        return mb_state[button];
    }

    // METODOS DEL CONTROLADOR

    /// Comprueba si hay un controlador de juego conectado
    /// @return True si hay un controlador de juego conectado, false en caso contrario
    inline bool IsGameControllerConnected() {
        return is_game_controller_connected;
    }

    /// Comprueba si un boton especifico del controlador de juego esta presionado
    /// @param button -> El boton del controlador de juego a comprobar
    /// @return True si se presiona el boton especificado, false en caso contrario
    bool IsGamePadButtonDown(TI_GameControllerButton button);

    /// Comprueba el valor de un eje especifico del controlador
    /// @param axis -> El eje del joystick o gatillo a comprobar
    /// @return El valor del eje del joystick o gatillo especificado (en el rango de -1 a 1)
    float GetJoystickAxisState(TI_GameControllerAxis axis);


private:

    /// Inicializa el sistema de entrada (llamado solo una vez como parte de Singleton)
    TonInput() {
        kb_state = SDL_GetKeyboardState(0);
        ClearState(true);
    }

    /// Actualiza el estado del evento de tecla presionada
    inline void OnKeyDown(const SDL_Event&) {
        is_key_down_event = true;
    }

    /// Actualiza el estado del evento de tecla liberada
    inline void OnKeyUp(const SDL_Event&) {
        is_key_up_event = true;
    }

    /// Actualiza el estado del movimiento del raton (posicion y si se esta moviendo o no)
    /// @param -> event El evento SDL que contiene informacion sobre el movimiento del raton
    inline void OnMouseMotion(const SDL_Event& event) {
        is_mouse_motion_event = true;
        mouse_pos.first = event.motion.x;
        mouse_pos.second = event.motion.y;
    }

    /// Actualiza el estado de los botones del raton
    /// @param event -> El evento SDL que contiene informacion sobre el boton del raton
    /// @param isDown -> True si se presiona el boton del raton, false si se suelta
    inline void OnMouseButtonChange(const SDL_Event& event, bool isDown) {
        is_mouse_button_event = true;
        switch (event.button.button) {
        case SDL_BUTTON_LEFT:
            mb_state[TI_MOUSE_LEFT] = isDown;
            break;
        case SDL_BUTTON_MIDDLE:
            mb_state[TI_MOUSE_MIDDLE] = isDown;
            break;
        case SDL_BUTTON_RIGHT:
            mb_state[TI_MOUSE_RIGHT] = isDown;
            break;
        default:
            break;
        }
    }

    /// Maneja todos los eventos de ventana
    /// @param event -> El evento SDL que contiene informacion sobre la ventana
    inline void HandleWindowEvent(const SDL_Event& event) {
        switch (event.window.event) {
        case SDL_WINDOWEVENT_CLOSE:
            is_close_window_event = true;
            break;
        default:
            break;
        }
    }

    bool is_quit = false;
    float joystick_death_zone = 0.12;
    bool is_game_controller_connected;
    bool is_close_window_event;
    bool is_key_up_event;
    bool is_key_down_event;
    bool is_mouse_motion_event;
    bool is_mouse_button_event;
    std::pair<Sint32, Sint32> mouse_pos;
    std::array<bool, 3> mb_state;
    const Uint8* kb_state;
    SDL_GameController* controller;
};

/// Singleton instance
/// @return A pointer of the instance
inline TonInput& TI() {
    return *TonInput::Instance();
}
#endif // !TONINPUT