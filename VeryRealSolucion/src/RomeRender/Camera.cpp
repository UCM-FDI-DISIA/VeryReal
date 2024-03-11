#include "Camera.h"
#include <OgreViewport.h>
#include <iostream>
#include <Ogre.h>
#include <Vector3.h>
#include <Vector2.h>


using namespace VeryReal;
using namespace Ogre;

    Camara::Camara(std::string name, Ogre::ColourValue color, Ogre::RenderWindow* ogre_window,
        Ogre::SceneManager* mgr, VeryReal::Vector3 m_offset ){
       
        //camara
        mNode = mgr->getRootSceneNode()->createChildSceneNode(); //nodo  de la camara
        mNode->lookAt(Ogre::Vector3(0, 0, -1), Ogre::Node::TS_PARENT);
        mNode->setPosition(0, 0, 30);
        camara = mgr->createCamera(name); // objeto y camara en si 
        camara->setNearClipDistance(1); //queremos que serenderice lo mas cerca posible desde la camara
        mNode->attachObject(camara);
        vewport = ogre_window->addViewport(camara);

        //cambio de color de fondo
        vewport->setBackgroundColour(color);
         
    }
  
    Camara::~Camara()
    {
       
    }
    void Camara::InitComponent(string name, Vector3 color, Ogre::RenderWindow* ogre_window, Ogre::SceneManager* mgr, VeryReal::Vector3 m_offset) {
       

            //camara
            mNode = mgr->getRootSceneNode()->createChildSceneNode(); //nodo  de la camara
            mNode->lookAt(Ogre::Vector3(0, 0, -1), Ogre::Node::TS_PARENT);
            mNode->setPosition(0, 0, 30);
            camara = mgr->createCamera(name); // objeto y camara en si 
            camara->setNearClipDistance(1); //queremos que serenderice lo mas cerca posible desde la camara
            mNode->attachObject(camara);
            vewport = ogre_window->addViewport(camara);

            //cambio de color de fondo

            vewport->setBackgroundColour(Ogre::ColourValue(color.GetX(), color.GetY(),color.GetZ()));

    }

    void Camara::lookAt( VeryReal::Vector3 pos)
    {
        Ogre::Vector3 p(pos.GetX(), pos.GetY(), pos.GetZ());
        mNode->lookAt(p, Ogre::Node::TransformSpace::TS_PARENT);
    }

    void Camara::translate(float x, float y, float z)
    {
        mNode->translate(x, y, z, Ogre::Node::TransformSpace::TS_LOCAL);
    }

    void Camara::roll(float d)
    {
        mNode->roll(Ogre::Degree(d));
    }

    void Camara::yaw(float d)
    {
        mNode->yaw(Ogre::Degree(d));
    }

    void Camara::pitch(float d)
    {
        mNode->pitch(Ogre::Degree(d));
    }
    void Camara::Offset(VeryReal::Vector2 offset)
    {
        camara->setFrustumOffset(offset.GetX(), offset.GetY());
    }
    void Camara::setNearClipDistance(float t_clip)
    {
        camara->setNearClipDistance(t_clip);
    }

    void Camara::setFarClipDistance(float t_clip)
    {
        camara->setFarClipDistance(t_clip);
    }

    void Camara::setViewPortBackgroundColour(Ogre::ColourValue t_vp_color)
    {
        vewport->setBackgroundColour(t_vp_color);
    }

    void Camara::desactiveViewport()
    {
        vewport->setVisibilityMask(0);
    }

    void Camara::activeViewport()
    {
        vewport->setVisibilityMask(1);
    }
    void Camara::desactive()
    {
        vewport->setCamera(nullptr);
    }
    Ogre::SceneNode* Camara::getNode()
    {
        return mNode;
    }
    void Camara::active()
    {
        vewport->setCamera(camara);
    }

 
    
    