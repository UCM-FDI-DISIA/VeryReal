#pragma once
#ifdef VERYREAL_TONINPUTEXPORT
#define VERYREAL_TONINPUT __declspec(dllexport)
#else
#define VERYREAL_TONINPUT __declspec(dllimport)
#endif
