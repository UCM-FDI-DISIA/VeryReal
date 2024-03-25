#pragma once
#pragma warning(disable : 4251)
#include <OgreVector3.h>
#include <OgreVector4.h>
#pragma warning(default : 4251)

#include <Vector3.h>
#include <Vector4.h>

namespace VeryReal {
    Ogre::Vector3 VR2OgreV3(VeryReal::Vector3 vveryreal) {
        Ogre::Vector3f vec(vveryreal.GetX(), vveryreal.GetY(), vveryreal.GetZ());
        return vec;
    }
    VeryReal::Vector3 Ogre2VRV3(Ogre::Vector3 vogre) { return VeryReal::Vector3(vogre.x, vogre.y, vogre.z); }
    Ogre::Vector4 VR2OgreV4(VeryReal::Vector4 vveryreal) {
        return Ogre::Vector4(vveryreal.GetR(), vveryreal.GetG(), vveryreal.GetB(), vveryreal.GetA());
    }
    VeryReal::Vector4 Ogre2VRV4(Ogre::Vector4 vogre) 
    { 
        return VeryReal::Vector4(vogre.x, vogre.y, vogre.z, vogre.w); 
    }
};
