#pragma once
#include <string>
#include <Vector3.h>
#include <OgreVector3.h>


namespace VeryReal {
	//clase para crear una ventana en nuestro motor
	inline Ogre::Vector3 VRconversorOgre(Vector3 vveryreal) {
		return Ogre::Vector3(vveryreal.GetX(), vveryreal.GetY(), vveryreal.GetZ());
	}
	inline Vector3 OgreconversorVR(Ogre::Vector3 vogre) {
		return Vector3(vogre.x, vogre.y, vogre.z );
	}
}

