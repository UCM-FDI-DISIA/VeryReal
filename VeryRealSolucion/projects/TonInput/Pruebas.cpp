
#include <iostream>
#include <crtdbg.h> //memory
#include <SDL.h>
#undef main
#include <stdlib.h>
#include <TonInput.h>
using namespace std;

int main()
{
	const int FRAME_RATE = 3;
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* mWindow;
	mWindow = SDL_CreateWindow("Very Real", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		854, 480, SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
	SDL_Renderer* renderer = SDL_CreateRenderer(mWindow, NULL, SDL_RENDERER_SOFTWARE);

	uint32_t startTime, frameTime;
	startTime = SDL_GetTicks();
	while (true) {
		frameTime = SDL_GetTicks() - startTime;
		TI().Refresh(); // Ih se actualiza (actua como el handleEvents())
		if (frameTime >= FRAME_RATE) {

			if (TI().IsKeyDown(SDL_SCANCODE_X))
				cout << "X" << endl;

			if (TI().IsGamePadButtonDown(SDL_CONTROLLER_BUTTON_X))
				cout << "boton1" << endl;
			if (TI().IsGamePadButtonDown(SDL_CONTROLLER_BUTTON_A))
				cout << "boton2" << endl;
			if (TI().IsGamePadButtonDown(SDL_CONTROLLER_BUTTON_B))
				cout << "boton3" << endl;

			if (TI().GetJoystickAxisState(SDL_CONTROLLER_AXIS_LEFTX) != 0)
				cout << TI().GetJoystickAxisState(SDL_CONTROLLER_AXIS_LEFTX) << endl;
			if (TI().GetJoystickAxisState(SDL_CONTROLLER_AXIS_RIGHTY) != 0)
				cout << TI().GetJoystickAxisState(SDL_CONTROLLER_AXIS_RIGHTY) << endl;

			if (TI().GetJoystickAxisState(SDL_CONTROLLER_AXIS_TRIGGERLEFT) != 0)
				cout << TI().GetJoystickAxisState(SDL_CONTROLLER_AXIS_TRIGGERLEFT) << endl;

			startTime = SDL_GetTicks();
		}
	}

	if (mWindow != nullptr)
	{
		SDL_DestroyWindow(mWindow);
		mWindow = nullptr;
		SDL_Quit();
	}


	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
	_CrtDumpMemoryLeaks();
	std::cout << "Hello World!\n";
}