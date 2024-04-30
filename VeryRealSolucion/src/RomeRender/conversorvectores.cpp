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

    Ogre::Quaternion VR2OgreQuaternion(VeryReal::Vector4 vveryreal) { 
        return Ogre::Quaternion(vveryreal.GetX(), vveryreal.GetY(), vveryreal.GetZ(), vveryreal.GetW()); 
    }

}