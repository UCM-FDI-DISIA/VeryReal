#ifndef INPUTMANAGER
#define INPUTMANAGER
#pragma once

#include <Manager.h>
#include <array>
#include "TonMapeo.h"
#include "exportTonInput.h"

#pragma warning(disable : 4251)

struct _SDL_GameController;
typedef struct _SDL_GameController SDL_GameController;
typedef union SDL_Event SDL_Event;

namespace  VeryReal {
class VERYREAL_TONINPUT InputManager : public VeryReal::Manager<InputManager> {
        private:
     InputManager() { }
  
    public:
        /// Inicializa el sistema de entrada (llamado solo una vez como parte de Singleton)

     virtual ~InputManager() { }
     static bool Init() {
                InputManager* a = new InputManager();
        if (a != nullptr) {
            instance_pointer.reset(a);
            return true;
        }
        return false;
    }
        // Inicializa SDL
     virtual void InitManager();

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

        
        /// Activamos el evento quit
        /// @return True si se ha activado el evento "quit", false en caso contrario
     inline void Quit() { is_quit = true; }

        /// Comprueba si se ha activado el evento "quit"
        /// @return True si se ha activado el evento "quit", false en caso contrario
     inline bool getQuit() { return is_quit; }

        /// Comprueba si el raton esta recibiendo algun evento de boton
        /// @return True si el raton esta recibiendo algun evento de boton, false en caso contrario
     inline bool MouseButtonEvent() {
            return is_mouse_button_event;
        }

        /// Comprueba la posicion del raton
        /// @return Un par que contiene las coordenadas x e y de la posicion del raton
     inline const std::pair<int32_t, int32_t>& GetMousePos() {
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
        void OnMouseMotion(const SDL_Event& event);

        /// Actualiza el estado de los botones del raton
        /// @param event -> El evento SDL que contiene informacion sobre el boton del raton
        /// @param isDown -> True si se presiona el boton del raton, false si se suelta
        void OnMouseButtonChange(const SDL_Event& event, bool isDown);

        /// Maneja todos los eventos de ventana
        /// @param event -> El evento SDL que contiene informacion sobre la ventana
        void HandleWindowEvent(const SDL_Event& event);

        bool is_quit = false;
        float joystick_death_zone = 0.12f;
        bool is_game_controller_connected = false;
        bool is_close_window_event = false;
        bool is_key_up_event = false;
        bool is_key_down_event = false;
        bool is_mouse_motion_event = false;
        bool is_mouse_button_event = false;
        std::pair<int32_t, int32_t> mouse_pos;
        std::array<bool, 3> mb_state = {false, false, false};
        const uint8_t* kb_state = nullptr;
        SDL_GameController* controller = nullptr;
    };
}

#pragma warning(default : 4251)

#endif 
// !InputManager