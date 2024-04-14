#include "conversorvectores.h"

#include <Vector2.h>
#include <Vector3.h>
#include <Vector4.h>

namespace VeryReal {
    Ogre::Vector2 VR2OgreV2(VeryReal::Vector2 vveryreal) { 
        Ogre::Vector2f vec(vveryreal.GetX(), vveryreal.GetY());
        return vec;
    }

    VeryReal::Vector2 Ogre2VRV2(Ogre::Vector2 vogre) { 
        return VeryReal::Vector2(vogre.x, vogre.y);
    }

    Ogre::Vector3 VR2OgreV3(VeryReal::Vector3 vveryreal) {
        return Ogre::Vector3f (vveryreal.GetX(), vveryreal.GetY(), vveryreal.GetZ());
    }

    VeryReal::Vector3 Ogre2VRV3(Ogre::Vector3 vogre) { 
        return VeryReal::Vector3(vogre.x, vogre.y, vogre.z); 
    }

    Ogre::Vector4 VR2OgreV4(VeryReal::Vector4 vveryreal) { 
        return Ogre::Vector4(vveryreal.GetR(), vveryreal.GetG(), vveryreal.GetB(), vveryreal.GetA()); 
    }

    VeryReal::Vector4 Ogre2VRV4(Ogre::Vector4 vogre) { 
        return VeryReal::Vector4(vogre.x, vogre.y, vogre.z, vogre.w); 
    }
}