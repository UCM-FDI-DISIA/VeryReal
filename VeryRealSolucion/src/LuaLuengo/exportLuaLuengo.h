#pragma once
#ifdef VERYREAL_LUALUENGOEXPORT
#define VERYREAL_LUALUENGO __declspec(dllexport)
#else
#define VERYREAL_LUALUENGO __declspec(dllimport)
#endif