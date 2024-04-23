#pragma once
#ifndef VRCONVERT_H
#define VRCONVERT_H
#pragma warning(disable : 4251)
#include <OgreVector2.h>
#include <OgreVector3.h>
#include <OgreVector4.h>
#pragma warning(default : 4251)

namespace VeryReal {
	class Vector2;
	class Vector3;
	class Vector4;

	Ogre::Vector2 VR2OgreV2(VeryReal::Vector2 vveryreal);
    VeryReal::Vector2 Ogre2VRV2(Ogre::Vector2 vogre);
	Ogre::Vector3 VR2OgreV3(VeryReal::Vector3 vveryreal);
	VeryReal::Vector3 Ogre2VRV3(Ogre::Vector3 vogre);
	Ogre::Vector4 VR2OgreV4(VeryReal::Vector4 vveryreal);
	VeryReal::Vector4 Ogre2VRV4(Ogre::Vector4 vogre);
}

#endif   // VRCONVERT_H