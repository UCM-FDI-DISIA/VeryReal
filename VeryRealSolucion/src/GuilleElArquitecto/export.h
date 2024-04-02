#pragma once
#ifdef VERYREAL_EXPORT
#define VERYREAL_API __declspec(dllexport)
#else
#define VERYREAL_API __declspec(dllimport)
#endif