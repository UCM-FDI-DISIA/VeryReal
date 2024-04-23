#pragma once
#ifdef VERYREAL_PEDROBULLETEXPORT
#define VERYREAL_PEDROBULLET __declspec(dllexport)
#else
#define VERYREAL_PEDROBULLET __declspec(dllimport)
#endif