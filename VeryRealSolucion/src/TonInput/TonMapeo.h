#pragma once
#ifndef TONMAPEO
#define TONMAPEO 

typedef enum {
    TI_MOUSE_LEFT = 0, 
    TI_MOUSE_MIDDLE = 1, 
    TI_MOUSE_RIGHT = 2
}TI_MouseButton;

//Enum que describe todos los botones que puede tener un mando
typedef enum {
    TI_CONTROLLER_BUTTON_INVALID = -1,
    TI_CONTROLLER_BUTTON_A,
    TI_CONTROLLER_BUTTON_B,
    TI_CONTROLLER_BUTTON_X,
    TI_CONTROLLER_BUTTON_Y,
    TI_CONTROLLER_BUTTON_BACK,
    TI_CONTROLLER_BUTTON_GUIDE,
    TI_CONTROLLER_BUTTON_START,
    TI_CONTROLLER_BUTTON_LEFTSTICK,
    TI_CONTROLLER_BUTTON_RIGHTSTICK,
    TI_CONTROLLER_BUTTON_LEFTSHOULDER,
    TI_CONTROLLER_BUTTON_RIGHTSHOULDER,
    TI_CONTROLLER_BUTTON_DPAD_UP,
    TI_CONTROLLER_BUTTON_DPAD_DOWN,
    TI_CONTROLLER_BUTTON_DPAD_LEFT,
    TI_CONTROLLER_BUTTON_DPAD_RIGHT,
    TI_CONTROLLER_BUTTON_MISC1,   
    TI_CONTROLLER_BUTTON_MAX
}TI_GameControllerButton;

//Enum que describe todos los ejes que puede tener un mando.
//Estos incluyen tantos los joysticks como los gatillos.
typedef enum {
    TI_CONTROLLER_AXIS_INVALID = -1,
    TI_CONTROLLER_AXIS_LEFTX,
    TI_CONTROLLER_AXIS_LEFTY,
    TI_CONTROLLER_AXIS_RIGHTX,
    TI_CONTROLLER_AXIS_RIGHTY,
    TI_CONTROLLER_AXIS_TRIGGERLEFT,
    TI_CONTROLLER_AXIS_TRIGGERRIGHT,
    TI_CONTROLLER_AXIS_MAX
}TI_GameControllerAxis;

//Todas las teclas posibles en un teclado
typedef enum {
     TI_SCANCODE_UNKNOWN = 0,
     TI_SCANCODE_A = 4,
     TI_SCANCODE_B = 5,
     TI_SCANCODE_C = 6,
     TI_SCANCODE_D = 7,
     TI_SCANCODE_E = 8,
     TI_SCANCODE_F = 9,
     TI_SCANCODE_G = 10,
     TI_SCANCODE_H = 11,
     TI_SCANCODE_I = 12,
     TI_SCANCODE_J = 13,
     TI_SCANCODE_K = 14,
     TI_SCANCODE_L = 15,
     TI_SCANCODE_M = 16,
     TI_SCANCODE_N = 17,
     TI_SCANCODE_O = 18,
     TI_SCANCODE_P = 19,
     TI_SCANCODE_Q = 20,
     TI_SCANCODE_R = 21,
     TI_SCANCODE_S = 22,
     TI_SCANCODE_T = 23,
     TI_SCANCODE_U = 24,
     TI_SCANCODE_V = 25,
     TI_SCANCODE_W = 26,
     TI_SCANCODE_X = 27,
     TI_SCANCODE_Y = 28,
     TI_SCANCODE_Z = 29,
     TI_SCANCODE_1 = 30,
     TI_SCANCODE_2 = 31,
     TI_SCANCODE_3 = 32,
     TI_SCANCODE_4 = 33,
     TI_SCANCODE_5 = 34,
     TI_SCANCODE_6 = 35,
     TI_SCANCODE_7 = 36,
     TI_SCANCODE_8 = 37,
     TI_SCANCODE_9 = 38,
     TI_SCANCODE_0 = 39,
     TI_SCANCODE_RETURN = 40,
     TI_SCANCODE_ESCAPE = 41,
     TI_SCANCODE_BACKSPACE = 42,
     TI_SCANCODE_TAB = 43,
     TI_SCANCODE_SPACE = 44,
     TI_SCANCODE_MINUS = 45,
     TI_SCANCODE_EQUALS = 46,
     TI_SCANCODE_LEFTBRACKET = 47,
     TI_SCANCODE_RIGHTBRACKET = 48,
     TI_SCANCODE_BACKSLASH = 49,
     TI_SCANCODE_NONUSHASH = 50, 
     TI_SCANCODE_SEMICOLON = 51,
     TI_SCANCODE_APOSTROPHE = 52,
     TI_SCANCODE_GRAVE = 53, 
     TI_SCANCODE_COMMA = 54,
     TI_SCANCODE_PERIOD = 55,
     TI_SCANCODE_SLASH = 56,
     TI_SCANCODE_CAPSLOCK = 57,
     TI_SCANCODE_F1 = 58,
     TI_SCANCODE_F2 = 59,
     TI_SCANCODE_F3 = 60,
     TI_SCANCODE_F4 = 61,
     TI_SCANCODE_F5 = 62,
     TI_SCANCODE_F6 = 63,
     TI_SCANCODE_F7 = 64,
     TI_SCANCODE_F8 = 65,
     TI_SCANCODE_F9 = 66,
     TI_SCANCODE_F10 = 67,
     TI_SCANCODE_F11 = 68,
     TI_SCANCODE_F12 = 69,
     TI_SCANCODE_PRINTSCREEN = 70,
     TI_SCANCODE_SCROLLLOCK = 71,
     TI_SCANCODE_PAUSE = 72,
     TI_SCANCODE_INSERT = 73,
     TI_SCANCODE_HOME = 74,
     TI_SCANCODE_PAGEUP = 75,
     TI_SCANCODE_DELETE = 76,
     TI_SCANCODE_END = 77,
     TI_SCANCODE_PAGEDOWN = 78,
     TI_SCANCODE_RIGHT = 79,
     TI_SCANCODE_LEFT = 80,
     TI_SCANCODE_DOWN = 81,
     TI_SCANCODE_UP = 82,
     TI_SCANCODE_NUMLOCKCLEAR = 83, 
     TI_SCANCODE_KP_DIVIDE = 84,
     TI_SCANCODE_KP_MULTIPLY = 85,
     TI_SCANCODE_KP_MINUS = 86,
     TI_SCANCODE_KP_PLUS = 87,
     TI_SCANCODE_KP_ENTER = 88,
     TI_SCANCODE_KP_1 = 89,
     TI_SCANCODE_KP_2 = 90,
     TI_SCANCODE_KP_3 = 91,
     TI_SCANCODE_KP_4 = 92,
     TI_SCANCODE_KP_5 = 93,
     TI_SCANCODE_KP_6 = 94,
     TI_SCANCODE_KP_7 = 95,
     TI_SCANCODE_KP_8 = 96,
     TI_SCANCODE_KP_9 = 97,
     TI_SCANCODE_KP_0 = 98,
     TI_SCANCODE_KP_PERIOD = 99,
     TI_SCANCODE_APPLICATION = 101, 
     TI_SCANCODE_POWER = 102,
     TI_SCANCODE_KP_EQUALS = 103,
     TI_SCANCODE_F13 = 104,
     TI_SCANCODE_F14 = 105,
     TI_SCANCODE_F15 = 106,
     TI_SCANCODE_F16 = 107,
     TI_SCANCODE_F17 = 108,
     TI_SCANCODE_F18 = 109,
     TI_SCANCODE_F19 = 110,
     TI_SCANCODE_F20 = 111,
     TI_SCANCODE_F21 = 112,
     TI_SCANCODE_F22 = 113,
     TI_SCANCODE_F23 = 114,
     TI_SCANCODE_F24 = 115,
     TI_SCANCODE_UNDO = 122,
     TI_SCANCODE_CUT = 123,
     TI_SCANCODE_COPY = 124,
     TI_SCANCODE_PASTE = 125, 
     TI_SCANCODE_FIND = 126, 
     TI_SCANCODE_MUTE = 127,
     TI_SCANCODE_VOLUMEUP = 128,
     TI_SCANCODE_VOLUMEDOWN = 129,
     TI_SCANCODE_KP_TAB = 186,
     TI_SCANCODE_KP_BACKSPACE = 187,
     TI_SCANCODE_KP_A = 188,
     TI_SCANCODE_KP_B = 189,
     TI_SCANCODE_KP_C = 190,
     TI_SCANCODE_KP_D = 191,
     TI_SCANCODE_KP_E = 192,
     TI_SCANCODE_KP_F = 193,
     TI_SCANCODE_KP_SPACE = 205,
     TI_SCANCODE_LCTRL = 224,
     TI_SCANCODE_LSHIFT = 225,
     TI_SCANCODE_LALT = 226,
     TI_SCANCODE_LGUI = 227,
     TI_SCANCODE_RCTRL = 228,
     TI_SCANCODE_RSHIFT = 229,
    
          
     TI_SCANCODE_BRIGHTNESSDOWN = 275,
     TI_SCANCODE_BRIGHTNESSUP = 276,
     TI_NUM_SCANCODES = 512 /**< not a key, just marks the number of scancodes */
}TI_KeyCode;


//Lista de eventos de SDL
typedef enum {
    TI_FIRSTEVENT = 0, /**< Unused (do not remove) */

    /* Application events */
    TI_QUIT = 0x100, /**< User-requested quit */

    /* These application events have special meaning on iOS, see README-ios.md for details */
    TI_APP_TERMINATING, /**< The application is being terminated by the OS
                          Called on iOS in applicationWillTerminate()
                          Called on Android in onDestroy()*/
    TI_APP_LOWMEMORY, /**< The application is low on memory, free memory if possible.
                          Called on iOS in applicationDidReceiveMemoryWarning()
                          Called on Android in onLowMemory()*/
    TI_APP_WILLENTERBACKGROUND, /**< The application is about to enter the background
                                     Called on iOS in applicationWillResignActive()
                                     Called on Android in onPause()*/
    TI_APP_DIDENTERBACKGROUND, /**< The application did enter the background and may not get CPU for some time
                                    Called on iOS in applicationDidEnterBackground()
                                    Called on Android in onPause()*/
    TI_APP_WILLENTERFOREGROUND, /**< The application is about to enter the foreground
                                     Called on iOS in applicationWillEnterForeground()
                                     Called on Android in onResume()*/
    TI_APP_DIDENTERFOREGROUND, /**< The application is now interactive
                                   Called on iOS in applicationDidBecomeActive()
                                   Called on Android in onResume()*/

    TI_LOCALECHANGED, /**< The user's locale preferences have changed. */

    /* Display events */
    TI_DISPLAYEVENT = 0x150, /**< Display state change */

    /* Window events */
    TI_WINDOWEVENT = 0x200, /**< Window state change */
    TI_SYSWMEVENT, /**< System specific event */

    /* Keyboard events */
    TI_KEYDOWN = 0x300, /**< Key pressed */
    TI_KEYUP, /**< Key released */
    TI_TEXTEDITING, /**< Keyboard text editing (composition) */
    TI_TEXTINPUT, /**< Keyboard text input */
    TI_KEYMAPCHANGED, /**< Keymap changed due to a system event such as an
                          input language or keyboard layout change.*/
    TI_TEXTEDITING_EXT, /**< Extended keyboard text editing (composition) */

    /* Mouse events */
    TI_MOUSEMOTION = 0x400, /**< Mouse moved */
    TI_MOUSEBUTTONDOWN, /**< Mouse button pressed */
    TI_MOUSEBUTTONUP, /**< Mouse button released */
    TI_MOUSEWHEEL, /**< Mouse wheel motion */

    /* Joystick events */
    TI_JOYAXISMOTION = 0x600, /**< Joystick axis motion */
    TI_JOYBALLMOTION, /**< Joystick trackball motion */
    TI_JOYHATMOTION, /**< Joystick hat position change */
    TI_JOYBUTTONDOWN, /**< Joystick button pressed */
    TI_JOYBUTTONUP, /**< Joystick button released */
    TI_JOYDEVICEADDED, /**< A new joystick has been inserted into the system */
    TI_JOYDEVICEREMOVED, /**< An opened joystick has been removed */
    TI_JOYBATTERYUPDATED, /**< Joystick battery level change */

    /* Game controller events */
    TI_CONTROLLERAXISMOTION = 0x650, /**< Game controller axis motion */
    TI_CONTROLLERBUTTONDOWN, /**< Game controller button pressed */
    TI_CONTROLLERBUTTONUP, /**< Game controller button released */
    TI_CONTROLLERDEVICEADDED, /**< A new Game controller has been inserted into the system */
    TI_CONTROLLERDEVICEREMOVED, /**< An opened Game controller has been removed */
    TI_CONTROLLERDEVICEREMAPPED, /**< The controller mapping was updated */
    TI_CONTROLLERTOUCHPADDOWN, /**< Game controller touchpad was touched */
    TI_CONTROLLERTOUCHPADMOTION, /**< Game controller touchpad finger was moved */
    TI_CONTROLLERTOUCHPADUP, /**< Game controller touchpad finger was lifted */
    TI_CONTROLLERSENSORUPDATE, /**< Game controller sensor was updated */

    /* Touch events */
    TI_FINGERDOWN = 0x700,
    TI_FINGERUP,
    TI_FINGERMOTION,

    /* Gesture events */
    TI_DOLLARGESTURE = 0x800,
    TI_DOLLARRECORD,
    TI_MULTIGESTURE,

    /* Clipboard events */
    TI_CLIPBOARDUPDATE = 0x900, /**< The clipboard or primary selection changed */

    /* Drag and drop events */
    TI_DROPFILE = 0x1000, /**< The system requests a file open */
    TI_DROPTEXT, /**< text/plain drag-and-drop event */
    TI_DROPBEGIN, /**< A new set of drops is beginning (NULL filename) */
    TI_DROPCOMPLETE, /**< Current set of drops is now complete (NULL filename) */

    /* Audio hotplug events */
    TI_AUDIODEVICEADDED = 0x1100, /**< A new audio device is available */
    TI_AUDIODEVICEREMOVED, /**< An audio device has been removed. */

    /* Sensor events */
    TI_SENSORUPDATE = 0x1200, /**< A sensor was updated */

    /* Render events */
    TI_RENDER_TARGETS_RESET = 0x2000, /**< The render targets have been reset and their contents need to be updated */
    TI_RENDER_DEVICE_RESET, /**< The device has been reset and all textures need to be recreated */

    /* Internal events */
    TI_POLLSENTINEL = 0x7F00, /**< Signals the end of an event poll cycle */

    TI_USEREVENT = 0x8000,

    TI_LASTEVENT = 0xFFFF /* This last event is only for bounding internal arrays */
}TI_Event;

#endif