#ifndef TONINPUT
#define TONINPUT
#pragma once

#include <vector>
#include "Singleton.h"
#include <array>
#include <SDL.h>
#include <TonMapeo.h>

using namespace std;

class TonInput : public Singleton<TonInput> {
    friend Singleton<TonInput>;

public:
  
    virtual ~TonInput() {}

    /// Clears the state of the input
    void ClearState(bool clearMouseButtons = false);

    /// Updates the input state with a new event
    void Update(const SDL_Event& event);

    /// Refreshes the input state of keyboard, controller and mouse
    void Refresh();

    /// Checks if a close window event has occurred
    /// @return True if a close window event has occurred, false otherwise
    inline bool CloseWindowEvent() {
        return is_close_window_event;
    }



    // KEYBOARD METHODS

    /// Checks if a key down event has occurred
    /// @return True if a key down event has occurred, false otherwise
    inline bool KeyDownEvent() {
        return is_key_down_event;
    }

    /// Checks if a key up event has occurred
    /// @return True if a key up event has occurred, false otherwise
    inline bool KeyUpEvent() {
        return is_key_up_event;
    }

    /// Checks if a specific key has just been pressed down
    /// @param key -> The SDL_Scancode of the key to check
    /// @return True if the specific key just down event has occurred, false otherwise
    inline bool IsKeyJustDown(TI_KeyCode key) {
        return KeyDownEvent() && kb_state[key] == 1;
    }

   

    /// Checks if a specific key is currently down
    /// @param key -> The SDL_Scancode of the key to check
    inline bool IsKeyDown(TI_KeyCode key) {
        return kb_state[key] == 1;
    }

  
    /// Checks if a specific key has just been released
    /// @param key -> The SDL_Scancode of the key to check
    inline bool IsKeyJustUp(TI_KeyCode key) {
        return KeyUpEvent() && kb_state[key] == 0;
    }

   

    /// Checks if a specific key is currently up
    /// @param key -> The SDL_Scancode of the key to check
    inline bool IsKeyUp(TI_KeyCode key) {
        return kb_state[key] == 0;
    }

  
    // MOUSE METHODS

    /// Checks if the mouse is receiving any motion event
    /// @return True if the mouse is receiving any motion event, false otherwise
    inline bool MouseMotionEvent() {
        return is_mouse_motion_event;
    }

    /// Checks if the event "quit" is activated
    /// @return True if the event "quit" is activated, false otherwise
    inline bool Quit() {
        return is_quit;
    }

    /// Checks if the mouse is receiving any button event
    /// @return True if the mouse is receiving any button event, false otherwise
    inline bool MouseButtonEvent() {
        return is_mouse_button_event;
    }

    /// Checks mouse position
    /// @return A pair containing the x and y coordinates of the mouse position
    inline const std::pair<Sint32, Sint32>& GetMousePos() {
        return mouse_pos;
    }

    /// Checks the state of a specific mouse button
    /// @param button -> The mouse button to check
    /// @return The state of the specified mouse button
    inline int GetMouseButtonState(TI_MouseButton button) {
        return mb_state[button];
    }



    //CONTROLLER METHODS

    /// Checks if there is a game controller connected
    /// @return True if a game controller is connected, false otherwise
    inline bool IsGameControllerConnected() {
        return is_game_controller_connected;
    }

    /// Checks if a specific button on the game controller is pressed
    /// @param button -> The button on the game controller to check
    /// @return True if the specified button is pressed, false otherwise
    bool IsGamePadButtonDown(TI_GameControllerButton button);

    /// Checks the value of a specific controller axis
    /// @param axis -> The joystick or trigger axis to check
    /// @return The value of the specified joystick or trigger axis (ranging from -1 to 1)
    float GetJoystickAxisState(TI_GameControllerAxis axis);


private:

    /// Initializes the input system (Called only once as part of Singleton)
    TonInput() {
        kb_state = SDL_GetKeyboardState(0);
        ClearState(true);
    }

    /// Updates the state of the key down event
    inline void OnKeyDown(const SDL_Event&) {
        is_key_down_event = true;
    }


    /// Updates the state of the key up event
    inline void OnKeyUp(const SDL_Event&) {
        is_key_up_event = true;
    }

    /// Updates the state of mouse motion (position and whether it's moving or not)
    /// @param -> event The SDL event containing mouse motion information
    inline void OnMouseMotion(const SDL_Event& event) {
        is_mouse_motion_event = true;
        mouse_pos.first = event.motion.x;
        mouse_pos.second = event.motion.y;
    }

    /// Updates the state of mouse buttons
    /// @param event -> The SDL event containing mouse button information
    /// @param isDown -> True if the mouse button is pressed, false if released
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

    /// Handles all window events
    /// @param event -> The SDL event containing window information
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