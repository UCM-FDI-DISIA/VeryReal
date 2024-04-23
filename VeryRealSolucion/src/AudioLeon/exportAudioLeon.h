#pragma once
#ifdef VERYREAL_AUDIOLEONEXPORT
#define VERYREAL_AUDIOLEON __declspec(dllexport)
#else
#define VERYREAL_AUDIOLEON __declspec(dllimport)
#endif
