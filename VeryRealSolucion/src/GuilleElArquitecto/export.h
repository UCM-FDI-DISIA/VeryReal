#pragma once
#ifdef VERYREAL_GUILLEELARQUITECTOEXPORT
#define VERYREAL_GUILLEELARQUITECTO __declspec(dllexport)
#else
#define VERYREAL_GUILLEELARQUITECTO __declspec(dllimport)
#endif

