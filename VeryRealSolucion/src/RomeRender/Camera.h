#pragma once
#include "Component.h"
#include <Ogre.h>
#include "Window.h"

namespace Ogre
{
    class Camera;
    class SceneNode;
    class SceneManager;
    class Viewport;
    class ColourValue;
}

namespace  VeryReal {
    class Camara: public Component {
    public:
        Camara(std::string name="", float t_color_x=0, float t_color_y=0, float t_color_z=0);
        virtual ~Camara();
        //virtual void Update();
        void InitComponent();

         void lookAt(Vector3 t_pos);
         void translate(float t_x, float t_y, float t_z);

         void roll(float t_d);
         void yaw(float t_d);
         void pitch(float t_d);
         void setAutoAspectRatio(bool t_b);
         void setNearClipDistance(float t_clip);
         void setFarClipDistance(float t_clip);

        void setViewPortBackgroundColour(Ogre::ColourValue t_vp_color);
        void desactiveViewport();
        void activeViewport();
        void desactive();
        void active();
        Ogre::SceneNode* getNode();

         void setOffset(Vector3 offset);
         void FollowTarget();
    protected:
        Ogre::SceneNode* mNode;
        Ogre::Camera* camara;
        Ogre::Viewport* vewport;
        Ogre::SceneManager* mgr;
        //referencia a la ventana 
        Vector3 m_offset;
        Ogre::ColourValue* color;
        std::string m_name;
        
    };


}
