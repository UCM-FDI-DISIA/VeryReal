#pragma once
#include "Component.h"

namespace Ogre
{
    class Camera;
    class SceneNode;
    class SceneManager;
    class Viewport;
    class ColourValue;
    class RenderWindow;

}

namespace  VeryReal {
    class Vector3;
    class Vector2;
    class Camara: public Component {
    public:
        Camara(std::string name, Ogre::ColourValue color, Ogre::RenderWindow* ogre_window, Ogre::SceneManager* mgr, VeryReal::Vector3 m_offset);
        virtual ~Camara();
        void lookAt(Vector3 pos);
        void translate(float x, float y, float z);
        void roll(float d);
        void yaw(float d);
        void pitch(float d);
        void Offset(VeryReal::Vector2 offset);
        void setNearClipDistance(float t_clip);
        void setFarClipDistance(float t_clip);
        void setViewPortBackgroundColour(Ogre::ColourValue color);
        void desactiveViewport();
        void activeViewport();
        void desactive();
        void active();
        Ogre::SceneNode* getNode();

        
    protected:
        Ogre::SceneNode* mNode;
        Ogre::Camera* camara;
        Ogre::Viewport* vewport;
        Ogre::SceneManager* mgr;
        //referencia a la ventana  NECESARIA
    };


}
