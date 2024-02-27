#ifndef TONINPUT
#define TONINPUT
#pragma once

#include <vector>
#include <Singleton.h>
#include <array>
#include <SDL.h>

using namespace std;
class TonInput : public Singleton<TonInput> {
    friend Singleton<TonInput>;

public:
    enum MOUSEBUTTON : uint8_t {
        LEFT = 0, MIDDLE = 1, RIGHT = 2
    };

    virtual ~TonInput() {}

    // clear the state
    void clearState(bool clearMouseButtons = false);
       
    

    // update the state with a new event
    void update(const SDL_Event& event);
       
    

    // refresh
    void refresh();
       
  

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

    bool isGamePadButtonDown(SDL_GameControllerButton button);
    

    float getJoystickAxisState(SDL_GameControllerAxis axis);



private:

    bool isQuit = false;

    TonInput() {
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

inline TonInput& getInputRef() {
    return *TonInput::Instance();
}
#endif // !TONINPUT