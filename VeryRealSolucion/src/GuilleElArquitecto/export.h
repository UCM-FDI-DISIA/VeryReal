#pragma once
#ifdef VERYREAL_GUILLEELARQUITECTOEXPORT
#define VERYREAL_GUILLEELARQUITECTO __declspec(dllexport)
#else
#define VERYREAL_GUILLEELARQUITECTO __declspec(dllimport)
#endif



//
//#pragma once
//#ifndef VERYREAL_GUILLEELARQUITECTO
//#ifdef VERYREAL_GUILLEEXPORT
//#define VERYREAL_GUILLEELARQUITECTO __declspec(dllexport)
//#else
//#define VERYREAL_GUILLEELARQUITECTO __declspec(dllimport)
//#endif
//#endif