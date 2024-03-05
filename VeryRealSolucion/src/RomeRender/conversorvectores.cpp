#include <string>
#include <Vector3.h>
#include <OgreVector3.h>
#include <Vector4.h>
#include <OgreVector4.h>
#include "conversorvectores.h"

using namespace VeryReal;

//clase para convertir vectores de VR  Ogre 
inline Ogre::Vector3 conversor::VRconversorOgre(Vector3 vveryreal) {
	return Ogre::Vector3(vveryreal.GetX(), vveryreal.GetY(), vveryreal.GetZ());
}
inline Vector3 conversor::OgreconversorVR(Ogre::Vector3 vogre) {
	return Vector3(vogre.x, vogre.y, vogre.z);
}
inline Ogre::Vector4 conversor::VRconversorOgre(Vector4 vveryreal) {
	return Ogre::Vector4(vveryreal.GetR(), vveryreal.GetG(), vveryreal.GetB(), vveryreal.GetA());
}
inline Vector4 conversor::OgreconversorVR(Ogre::Vector4 vogre) {
	return Vector4(vogre.x, vogre.y, vogre.z, vogre.w);
}