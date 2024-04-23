#pragma once
#ifdef VERYREAL_ROMERENDEREXPORT
#define VERYREAL_ROMERENDER __declspec(dllexport)
#else
#define VERYREAL_ROMERENDER __declspec(dllimport)
#endif