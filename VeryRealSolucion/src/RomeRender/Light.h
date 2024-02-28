#pragma once
#include "Component.h"
#include "Vector3.h"

namespace Ogre
{
    class SceneNode;
    class SceneManager;
    class Light;
}

namespace  VeryReal {
    class Light {
    public:
        Light();
        ~Light();
        virtual void Update();
        void InitComponent();


        void SetDirection(Vector3 const& v);
        void setType(int const dir);

        void SetDiffuseColour(Vector3 const& color);
        void SetshadowFarDistance(float distance);

         void SetSpotlightInnerAngle(float dist);
         void SetSpotlightOuterAngle(float dist);

         void SetSpotlightNearClipDistance(float dist);
      
         void ActivateShadows(bool shdows);
    protected:
        Ogre::Light* light_;
        Ogre::SceneNode* mNode;
        Ogre::SceneManager* mngr_;
    };

		
}