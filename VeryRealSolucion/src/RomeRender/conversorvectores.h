#pragma once
#ifndef VRCONVERT_H
#define VRCONVERT_H

#pragma warning(disable : 4251)
#include <OgreVector3.h>
#include <OgreVector4.h>
#pragma warning(default : 4251)

namespace VeryReal {
	class Vector3;
	class Vector4;

	Ogre::Vector3 VR2OgreV3(VeryReal::Vector3 vveryreal);
	VeryReal::Vector3 Ogre2VRV3(Ogre::Vector3 vogre);
	Ogre::Vector4 VR2OgreV4(VeryReal::Vector4 vveryreal);
	VeryReal::Vector4 Ogre2VRV4(Ogre::Vector4 vogre);
}

#endif   // VRCONVERT_H