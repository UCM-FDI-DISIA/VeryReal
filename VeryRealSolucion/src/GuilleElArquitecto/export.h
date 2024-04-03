#pragma once
#ifdef VERYREAL_EXPORT
#define VERYREAL_API __declspec(dllexport)
#else
#define VERYREAL_API __declspec(dllimport)
#endif



//
//#pragma once
//#ifndef VERYREAL_API
//#ifdef VERYREAL_EXPORT
//#define VERYREAL_API __declspec(dllexport)
//#else
//#define VERYREAL_API __declspec(dllimport)
//#endif
//#endif