// This file is part of the course TPV2@UCM - Samir Genaim
// Added gameController suport
#pragma once
#include <iostream>
#include <SDL.h>
#include <array>
#include "Singleton.h"

// Instead of a Singleton class, we could make it part of
// SDLUtils as well.

class InputHandler : public Singleton<InputHandler> {
    friend Singleton<InputHandler>;

public:
    enum MOUSEBUTTON : uint8_t {
        LEFT = 0, MIDDLE = 1, RIGHT = 2
    };

    virtual ~InputHandler() {
    }

    // clear the state
    inline void clearState(bool clearMouseButtons = false) {
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

    // update the state with a new event
    inline void update(const SDL_Event& event) {
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

    // refresh
    inline void refresh() {
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

    // close window event
    inline bool closeWindowEvent() {
        return isCloseWindoEvent_;
    }

    // keyboard
    inline bool keyDownEvent() {
        return isKeyDownEvent_;
    }

    inline bool keyUpEvent() {
        return isKeyUpEvent_;
    }

    inline bool isKeyJustDown(SDL_Scancode key) {
        return keyDownEvent() && kbState_[key] == 1;
    }

    inline bool isKeyJustDown(SDL_Keycode key) {
        return isKeyDown(SDL_GetScancodeFromKey(key));
    }

    inline bool isKeyDown(SDL_Scancode key) {
        return kbState_[key] == 1;
    }

    inline bool isKeyDown(SDL_Keycode key) {
        return isKeyDown(SDL_GetScancodeFromKey(key));
    }

    inline bool isKeyJustUp(SDL_Scancode key) {
        return keyUpEvent() && kbState_[key] == 0;
    }

    inline bool isKeyJustUp(SDL_Keycode key) {
        return isKeyJustUp(SDL_GetScancodeFromKey(key));
    }

    inline bool isKeyUp(SDL_Scancode key) {
        return kbState_[key] == 0;
    }

    inline bool isKeyUp(SDL_Keycode key) {
        return isKeyUp(SDL_GetScancodeFromKey(key));
    }

    // mouse
    inline bool mouseMotionEvent() {
        return isMouseMotionEvent_;
    }

    inline bool quit() {
        return isQuit;
    }

    inline bool mouseButtonEvent() {
        return isMouseButtonEvent_;
    }

    inline const std::pair<Sint32, Sint32>& getMousePos() {
        return mousePos_;
    }

    inline int getMouseButtonState(MOUSEBUTTON b) {
        return mbState_[b];
    }

    //controller
    inline bool isGameControllerConected() {
        return isGameControllerConected_;
    }

    inline bool isGamePadButtonDown(SDL_GameControllerButton button) {
        if (isGameControllerConected_) {
            if (SDL_GameControllerGetButton(controller_, button)) {
                return true;
            }
        }
        return false;
    }

    inline float getJoystickAxisState(SDL_GameControllerAxis axis) {
        if (isGameControllerConected_) {
            float axisState = SDL_GameControllerGetAxis(controller_, axis) / 32767.0;
            if (abs(axisState) > 1) axisState = round(axisState); // Corrección (los negativos llegan hasta -32768 y los positivos hasta 32767)
            else if(abs(axisState) < joystickDeathZone_) axisState = 0;
            return (axisState);
        }
        return 0; // Valor predeterminado si el joystick no está conectado o el eje no se está utilizando
    }

    // add support for Joystick, see Chapter 4 of
    // the book 'SDL Game Development'

private:

    bool isQuit = false;

    InputHandler() {
        kbState_ = SDL_GetKeyboardState(0);
        clearState(true);
    }

    inline void onKeyDown(const SDL_Event&) {
        isKeyDownEvent_ = true;
    }

    inline void onKeyUp(const SDL_Event&) {
        isKeyUpEvent_ = true;
    }

    inline void onMouseMotion(const SDL_Event& event) {
        isMouseMotionEvent_ = true;
        mousePos_.first = event.motion.x;
        mousePos_.second = event.motion.y;

    }

    inline void onMouseButtonChange(const SDL_Event& event, bool isDown) {
        isMouseButtonEvent_ = true;
        switch (event.button.button) {
        case SDL_BUTTON_LEFT:
            mbState_[LEFT] = isDown;
            break;
        case SDL_BUTTON_MIDDLE:
            mbState_[MIDDLE] = isDown;
            break;
        case SDL_BUTTON_RIGHT:
            mbState_[RIGHT] = isDown;
            break;
        default:
            break;
        }
    }

    inline void handleWindowEvent(const SDL_Event& event) {
        switch (event.window.event) {
        case SDL_WINDOWEVENT_CLOSE:
            isCloseWindoEvent_ = true;
            break;
        default:
            break;
        }
    }

    float joystickDeathZone_ = 0.12;
    bool isGameControllerConected_;
    bool isCloseWindoEvent_;
    bool isKeyUpEvent_;
    bool isKeyDownEvent_;
    bool isMouseMotionEvent_;
    bool isMouseButtonEvent_;
    std::pair<Sint32, Sint32> mousePos_;
    std::array<bool, 3> mbState_;
    const Uint8* kbState_;
    SDL_GameController* controller_;
};

// This macro defines a compact way for using the singleton InputHandler, instead of
// writing InputHandler::instance()->method() we write ih().method()
inline InputHandler& ih() {
    return *InputHandler::Instance();
}